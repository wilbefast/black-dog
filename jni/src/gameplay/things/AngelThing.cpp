/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "AngelThing.hpp"

#include "../../global.hpp"
#include "../../resources/AudioManager.hpp"
#include "../../resources/GraphicsManager.hpp"
#include "elements/ColliderElement.hpp"
#include "events/CollisionEvent.hpp"
#include "../../scenes/BlackDogState.hpp"

#include "FallingThing.hpp"

#define STR_UNSTUN "unstun"
#define STR_REFEATHER "refeather"
#define STR_ANIMATION_END "animation_end"
#define STR_DEATH "death"
#define STR_COLLISION "collision"
#define STR_ORB_USED "orb_used"

/// CONSTANTS

// resource caching

// numeric values
const float AngelThing::BOUNCE_BACK = 5.0f;
const float AngelThing::BOUNCE_DOWN = 2.0f;
const float AngelThing::BOUNCE_UP = 6.0f;
const float AngelThing::THRUST = 6.0f;
const float AngelThing::FRICTION = 0.2f;
const float AngelThing::SPEED_H_INC = 0.01f;
const float AngelThing::SPEED_H_MAX = 0.1f;
const float AngelThing::SPEED_H_ORB = 7.0f;

// first number is gravity, second is max speed
const AngelThing::State AngelThing::FLAPPING(0.2f, 0.2f),
                        AngelThing::GLIDING(0.1f, 0.7f),
                        AngelThing::FALLING(0.3f, 10.0f),
                        AngelThing::STUNNED(0.3f, 5.0f),
                        AngelThing::BOOSTING(0.0f, 1.0f),
                        AngelThing::DEAD(1.0f, 0.0f);

/// PLAYER STATES

unsigned int AngelThing::State::next_id = 0;

AngelThing::State::State(float _gravity, float _speed_max) :
gravity(_gravity),
speed_max(_speed_max),
id(State::next_id)
{
  AngelThing::State::next_id++;
}

bool AngelThing::State::operator==(const AngelThing::State& other) const
{
  return (id == other.id);
}


/// CONSTRUCTION & DESTRUCTION


AngelThing::AngelThing(V2i _position) :
Thing(_position, "angel"),
state(&FALLING),
graphic(this, V2f(96, 48)),
movement(this),
feathers(this, MAX_FEATHERS),
orbs(this, MAX_ORBS, 0),
stun_timer(this, STR_UNSTUN),
feather_timer(this, STR_REFEATHER, FEATHER_INTERVAL),
orb_use_timer(this, STR_ORB_USED, ORB_USE_INTERVAL),
furthest_x(_position.x)
{
  // not using orbs by default
  orb_use_timer.unset();

  // set initial sprite
  graphic.setSprite(GraphicsManager::getInstance()->
                    get_animation("wraith_fall"), 0.1f);

  // angel is collideable
  body = new ColliderElement(this, V2d(V2d(HITBOX_W, HITBOX_H)));
}

/// OVERRIDES

void AngelThing::draw()
{
  // draw the sprite
  graphic.draw();
}

int AngelThing::update(GameState* context, float delta)
{
  // collect the result at each step of the way, check for interruptions
  int result = GameState::CONTINUE;

  // treat input
  result = treatInput(context);
  if(result != GameState::CONTINUE)
    return result;

  // move based on input and physics
  V2f speed = movement.getSpeed(), position = getPosition();
  // apply gravity
  speed += V2f(0.0f, state->gravity);
  // advance towards the right
  if(speed.x < 0.0f || (position.x > MAX_X && state != &BOOSTING) || speed.x > SPEED_H_MAX)
    speed.x = (ABS(speed.x) > SPEED_H_INC) ? speed.x * 0.9f : 0.0f;
  else
    speed.x = (speed.x < SPEED_H_MAX-SPEED_H_INC) ?
                speed.x+SPEED_H_INC : SPEED_H_MAX;
  // apply terminal velocity
  if(speed.y > state->speed_max)
    speed.y = state->speed_max;
  // update position
  movement.setSpeed(speed);
  movement.update(context, delta);
  // update best progress so far
  if(position.x > furthest_x)
    furthest_x = position.x;

  // decrement timers
  if(stun_timer.ticking())
    stun_timer.decrement(delta);
  if(feather_timer.ticking())
    feather_timer.decrement(delta);
  if(orb_use_timer.ticking())
    orb_use_timer.decrement(delta);

  // check for death
  result = checkCollision(context);
  if(result != GameState::CONTINUE)
    return result;

  // animate the sprite
  graphic.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  for(EventIter i = events.begin();
      result == GameState::CONTINUE && i != events.end(); i++)
    result = treatEvent(*i, context);
  if(result != GameState::CONTINUE)
    return result;

  // nothing interrupted execution, so continue looping
  return Thing::update(context, delta);
}

/// QUERY

V2f AngelThing::getPrevPosition() const
{
  return movement.getPrevPos();
}

int AngelThing::countFeathers() const
{
  return feathers.getBalance();
}

int AngelThing::countOrbs() const
{
  return orbs.getBalance();
}

float AngelThing::getFurthestX() const
{
  return furthest_x;
}


/// SUBROUTINES

void AngelThing::setState(State const& new_state, GameState* context)
{
  // cache animations used by this Thing
  static Animation
    *wraith_fall = GraphicsManager::getInstance()->get_animation("wraith_fall"),
    *wraith_flap = GraphicsManager::getInstance()->get_animation("wraith_flap"),
    *wraith_stun = GraphicsManager::getInstance()->get_animation("wraith_stun"),
    *wraith_boost = GraphicsManager::getInstance()->get_animation("wraith_boost"),
    *feather = GraphicsManager::getInstance()->get_animation("feather");


  // FALL
  if(new_state == FALLING && state == &GLIDING)
    graphic.setSprite(wraith_fall, 0.1f);

  // FLAP
  else if(new_state == FLAPPING)
  {
    // flap wings
    AudioManager::getInstance()->play_sound("flap");
    movement.setSpeed(V2f(movement.getSpeed().x, -THRUST));
    feather_timer.set(FEATHER_INTERVAL);
    graphic.setSprite(wraith_flap, 0.1f);
    graphic.setFrame(0.0f);

    // create feather
    context->addThing(new FallingThing(position+V2f(-16, -16), "feather", feather, 0.1f, 0.3f));
  }

  // STUNNED
  else if(new_state == STUNNED)
  {
    stun_timer.set(STUN_DURATION);
    feather_timer.set(FEATHER_INTERVAL);
    graphic.setSprite(wraith_stun, 0.1f);
    AudioManager::getInstance()->play_sound("scream");
    // some orbs are lost
    unsigned int n_lost = (orbs.getBalance() >= ORB_COLLISION_PENALTY)
              ? orbs.tryWithdraw(ORB_COLLISION_PENALTY)
              : orbs.withdrawAll();

    // create the orbs
    static Animation* orb = GraphicsManager::getInstance()->get_animation("orb");
    for(unsigned int i = 0; i < n_lost; i++)
    {
      V2f spawn_pos(position.x - RAND_BETWEEN(24, 32),
                    position.y + RAND_BETWEEN(-16, 16));
      context->addThing(new FallingThing(spawn_pos, "dead_orb", orb, 0.1f, 0.2f));
    }
  }

  // BOOSTING
  else if(new_state == BOOSTING)
  {
    graphic.setSprite(wraith_boost, 0.1f);
    movement.addSpeed(V2f(SPEED_H_ORB, -movement.getSpeed().y*0.8f));
  }

  // DEAD
  else if(new_state == DEAD)
    AudioManager::getInstance()->play_sound("swallow");

  // overwrite the previous start at the very end!
  state = &new_state;
}

int AngelThing::treatEvent(ThingEvent* event, GameState* context)
{
  // cache animations used by this Thing
  static Animation
    *wraith_fall = GraphicsManager::getInstance()->get_animation("wraith_fall"),
    *wraith_glide = GraphicsManager::getInstance()->get_animation("wraith_glide");

  // local variables
  static str_id UNSTUN = numerise(STR_UNSTUN),
                REFEATHER = numerise(STR_REFEATHER),
                ANIMATION_END = numerise(STR_ANIMATION_END),
                DEATH = numerise(STR_DEATH),
                COLLISION = numerise(STR_COLLISION),
                ORB_USED = numerise(STR_ORB_USED);

  // stun duration finished event
  if(event->getType() == UNSTUN)
    setState(FALLING, context);

  // feather regeration finished event
  else if (event->getType() == REFEATHER)
  {
    feathers.deposit();
    // remember to reset the timer
    feather_timer.set(FEATHER_INTERVAL);
  }

  // orb consumed by boost event
  else if (event->getType() == ORB_USED && state == &BOOSTING)
  {
    if(!orbs.tryWithdraw())
      // stop boosting
      setState(FALLING, context);
    else
      // remember to reset the timer
      orb_use_timer.set(ORB_USE_INTERVAL);
  }

  // animation end
  else if (event->getType() == ANIMATION_END)
  {
    if(state == &FALLING)
      graphic.setSprite(wraith_fall, 0.1f);
    else if (state == &GLIDING)
      graphic.setSprite(wraith_glide, 0.1f);
  }

  // death
  else if (event->getType() == DEATH)
  {
    setState(DEAD, context);
    return GameState::LOSE_LEVEL;
  }

  // collision
  else if(event->getType() == COLLISION)
  {
    // get other
    Thing* other = ((CollisionEvent*)event)->getOther();

    // cache possible colliders
    static str_id orb = numerise("orb");

    // collide with orb
    if(state != &STUNNED && state != &BOOSTING && other->getType() == orb && !orbs.isFull())
    {
      // consume the orb
      other->die();
      orbs.deposit();
    }
  }

  // nothing to report
  return GameState::CONTINUE;
}

int AngelThing::treatInput(GameState* context)
{
  // get an input handle and read updates
  GameState::Input* input = context->getInput();

  // pressing this step
  if(input->clicking)
  {
    if(state == &FALLING)
    {
      if(!input->clicking_previous)
      {
        if(!orbs.isFull() && feathers.tryWithdraw())
          setState(FLAPPING, context);
        else if(orbs.isFull())
        {
          setState(BOOSTING, context);
          orbs.tryWithdraw();
          orb_use_timer.set(ORB_USE_INTERVAL);
        }
      }
      else
        setState(GLIDING, context);
    }

    // not clicking
    else if(state == &FLAPPING)
    {
      // if moving downwards
      if(movement.getSpeed().y > 0.0f)
        setState(GLIDING, context);
    }
  }

  // not pressing this step
  else
  {
    // stop boosting
    if(state == &BOOSTING)
    {
      setState(FALLING, context);
      orb_use_timer.unset();
    }

    // if moving upwards
    if(movement.getSpeed().y < 0.0f)
    // apply dampening: hold down longer to fly higher
    movement.addSpeed(V2f(0.0f, FRICTION));

    // if moving downwards
    else if(state == &GLIDING || state == &FLAPPING)
      setState(FALLING, context);
  }

  // nothing to report
  return GameState::CONTINUE;
}

int AngelThing::checkCollision(GameState* context)
{
  // local variables
  const TunnelFG* obstactle = ((BlackDogState*)context)->getObstacle();
  fRect hitbox = body->getOffsetBox();

  // check for collisions with the tunnel
  int collision = obstactle->collidingRect(hitbox), prev_collision = 0;
  if(collision)
  {
    // snap out of contact
    for(int snap_left = MAX_SNAP; snap_left && collision; snap_left--)
    {
      move(V2f(-1, -collision));
      hitbox = body->getOffsetBox();
      prev_collision = collision;
      collision = obstactle->collidingRect(hitbox);
    }
    // update position and speed
    movement.setSpeed(V2f(-BOUNCE_BACK, (prev_collision < 0) ? BOUNCE_DOWN : -BOUNCE_UP));
    // paralyse for a short duration
    setState(STUNNED, context);
    // give feather ONLY if none left
    if(!feathers.anyLeft())
      feathers.deposit();
  }

  // nothing to report
  return GameState::CONTINUE;
}
