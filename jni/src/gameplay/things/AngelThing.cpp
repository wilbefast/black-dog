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
#include "../../io/AudioManager.hpp"
#include "../../io/GraphicsManager.hpp"
#include "elements/ColliderElement.hpp"
#include "events/CollisionEvent.hpp"
#include "../../scenes/BlackDogState.hpp"

#include "FallingThing.hpp"
#include "EffectThing.hpp"
#include "EpilogueThing.hpp"

#define STR_UNSTUN "unstun"
#define STR_REFEATHER "refeather"
#define STR_ANIMATION_END "animation_end"
#define STR_DEATH "death"
#define STR_COLLISION "collision"
#define STR_ORB_USED "orb_used"

/// CONSTANTS

// resource caching

// numeric values
const float AngelThing::BOUNCE_BACK_WALL = 7.0f;
const float AngelThing::BOUNCE_BACK_MINION = 6.0f;
const float AngelThing::BOUNCE_BACK_IMP = 2.0f;
const float AngelThing::BOUNCE_DOWN = 2.0f;
const float AngelThing::BOUNCE_UP = 6.0f;
const float AngelThing::THRUST = 6.0f;
const float AngelThing::FRICTION = 0.2f;
const float AngelThing::SPEED_X_INC = 0.01f;
const float AngelThing::SPEED_X_MAX = 0.1f;
const float AngelThing::SPEED_X_BOOST = 0.4f;
const float AngelThing::SPEED_Y_BOOST = 2.5f;
const float AngelThing::DELTA_Y_BOOST = 0.2f;

// first number is gravity, second is max speed
const AngelThing::State AngelThing::FLAPPING(0.2f, 0.2f),
                        AngelThing::GLIDING(0.1f, 0.7f),
                        AngelThing::FALLING(0.3f, 10.0f),
                        AngelThing::STUNNED(0.3f, 5.0f),
                        AngelThing::BOOSTING(0.0f, SPEED_Y_BOOST),
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
state(&GLIDING),
graphic(this, V2f(96, 48)),
buff(this, V2f(20, 20)),
auto_glide(true),
movement(this),
feathers(this, MAX_FEATHERS),
orbs(this, MAX_ORBS, 0),
stun_timer(this, STR_UNSTUN),
feather_timer(this, STR_REFEATHER, FEATHER_INTERVAL),
orb_use_timer(this, STR_ORB_USED),
furthest_x(_position.x)
{
  // set initial sprites
  graphic.setSprite(GraphicsManager::getInstance()->
                    get_animation("wraith_glide"), 0.1f);
  buff.setSprite(GraphicsManager::getInstance()->
                    get_animation("orb_consume"), 0.1f);
  buff.setHidden(true);

  // angel is collideable
  body = new ColliderElement(this, V2d(V2d(HITBOX_W, HITBOX_H)));
    // freed by ~Thing
}

/// OVERRIDES

void AngelThing::draw()
{
  // draw the sprite
  graphic.draw();

  // draw effects on top
  buff.draw();
}

int AngelThing::update(GameState* context, float delta)
{
  // lose as soon as state is unpaused
  if(state == &DEAD)
    return GameState::LOSE_LEVEL;

  // collect the result at each step of the way, check for interruptions
  int result = GameState::CONTINUE;

  // animate the sprites
  graphic.update(context, delta);
  buff.update(context, delta);

  // victory
  if(((BlackDogState*)context)->getDifficulty() < 0.0f)
  {
    context->addThing(new EpilogueThing(position));
    return GameState::DELETE_ME;
  }

  // treat input
  result = treatInput(context);
  if(result != GameState::CONTINUE)
    return result;

  // move based on input and physics
  V2f speed = movement.getSpeed(), position = getPosition();
  // apply gravity
  speed.y += state->gravity * delta;
  // horizontal movement speed is fixed while boosting
  if(state != &BOOSTING)
  {
    if(speed.x < 0.0f || position.x > furthest_x || speed.x > SPEED_X_MAX)
      speed.x = (ABS(speed.x) > SPEED_X_INC) ? speed.x * 0.9f : 0.0f;
    else
      speed.x = (speed.x < SPEED_X_MAX-SPEED_X_INC) ?
                  speed.x+SPEED_X_INC : SPEED_X_MAX;
  }
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
  // stop multiple instances of transition sound being played at once
  if(state == &new_state)
    return;

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
    // first input cancels auto-glide
    auto_glide = false;

    // flap wings
    AudioManager::getInstance()->play_sound("wraith_flap");
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
    AudioManager::getInstance()->play_sound("wraith_hurt");
  }

  // BOOSTING
  else if(new_state == BOOSTING)
  {
    graphic.setSprite(wraith_boost, 0.1f);
    movement.addSpeed(V2f(SPEED_X_BOOST, -movement.getSpeed().y*0.8f));
    AudioManager::getInstance()->play_sound("wraith_boost");
  }

  // DEAD
  else if(new_state == DEAD)
  {
    AudioManager::getInstance()->play_sound("wraith_die");
    context->pause(MAX_FPS * 3);
  }

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
  if(state == &STUNNED && event->getType() == UNSTUN)
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
    {
      // stop boosting
      setState(GLIDING, context);
      auto_glide = true;
    }
    else
      // remember to reset the timer
      orb_use_timer.set(ORB_USE_INTERVAL);
  }

  // animation end
  else if (event->getType() == ANIMATION_END)
  {
    // main graphic
    if(event->getSender() == &graphic)
    {
      if(state == &FALLING)
        graphic.setSprite(wraith_fall, 0.1f);
      else if (state == &GLIDING)
        graphic.setSprite(wraith_glide, 0.1f);
    }

    // special effect graphic
    if(event->getSender() == &buff)
      buff.setHidden(true);
  }

  // death
  else if (event->getType() == DEATH)
    setState(DEAD, context);

  // collision
  else if(event->getType() == COLLISION)
  {
    // get other
    Thing* other = ((CollisionEvent*)event)->getOther();

    // cache possible colliders
    static str_id orb = numerise("orb"), minion = numerise("minion"),
                  imp = numerise("imp");


    // hit by cerberus head
    if(other->getType() == imp)
    {
      if(state != &STUNNED && state != &BOOSTING)
      {
        setState(STUNNED, context);
        movement.setSpeed(V2f(-BOUNCE_BACK_IMP, 0.0f));
        tryDropOrbs(ORB_PENALTY_IMP, context);
      }
      // always kill the other, even if stunned!
      AudioManager::getInstance()->play_sound("imp_die");
      context->addThing(new EffectThing((V2i)other->getPosition(),
              GraphicsManager::getInstance()->get_animation("imp_die"), 0.1f));
      other->die();

    }

    if(state != &STUNNED)
    {
      // hit by minion
      if(other->getType() == minion && state != &BOOSTING)
      {
        setState(STUNNED, context);
        movement.setSpeed(V2f(-BOUNCE_BACK_MINION, 0.0f));
        tryDropOrbs(ORB_PENALTY_MINION, context);
      }

      // collide with orb
      if(other->getType() == orb)
      {
        // create special effect
        buff.setFrame(0.0f);
        buff.setHidden(false);

        // consume the orb
        other->die();
        orbs.deposit();

        // boost if full
        if(orbs.isFull() && state != &BOOSTING)
        {
          setState(BOOSTING, context);
          orb_use_timer.set(ORB_USE_INTERVAL);
          feathers.depositMax();

        }
        else
          AudioManager::getInstance()->play_sound("orb_die");
      } // if(other->getType() == orb)
    } // if(state != &STUNNED)
  } // if(event->getType() == COLLISION)

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
    if(state == &BOOSTING)
    {
      if(movement.getSpeedY() > -SPEED_Y_BOOST)
        movement.addSpeedY(-DELTA_Y_BOOST);
      else
        movement.setSpeedY(-SPEED_Y_BOOST);
    }

    else if(state == &FALLING || (state == &GLIDING && auto_glide))
    {

      if(!input->clicking_previous && feathers.tryWithdraw())
        setState(FLAPPING, context);
      else
        setState(GLIDING, context);
    }

    // not falling
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
    // downward boosting
    if(state == &BOOSTING)
    {
      if(movement.getSpeedY() < SPEED_Y_BOOST)
        movement.addSpeedY(DELTA_Y_BOOST);
      else
        movement.setSpeedY(SPEED_Y_BOOST);
    }

    // if moving upwards
    if(movement.getSpeed().y < 0.0f)
      // apply dampening: hold down longer to fly higher
      movement.addSpeed(V2f(0.0f, FRICTION));

    // if moving downwards
    else if(!auto_glide && (state == &GLIDING || state == &FLAPPING))
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
  V2i collision = obstactle->collidingRect(hitbox);
  if(collision)
  {
    // update position and speed
    move(-collision);
    movement.setSpeed(V2f( (collision.x > 0) ? -BOUNCE_BACK_WALL : -BOUNCE_BACK_WALL,
                           (collision.y < 0) ? BOUNCE_DOWN : -BOUNCE_UP));
    // paralyse for a short duration
    setState(STUNNED, context);
    tryDropOrbs(ORB_PENALTY_WALL, context);
    // give feather ONLY if none left
    if(!feathers.anyLeft())
      feathers.deposit();
  }

  // nothing to report
  return GameState::CONTINUE;
}

void AngelThing::tryDropOrbs(unsigned int n_lost, GameState* context)
{
  // some orbs are lost
  n_lost = orbs.tryWithdraw(n_lost);

  // create the orbs
  static Animation* orb_die = GraphicsManager::getInstance()->get_animation("orb_die");
  for(unsigned int i = 0; i < n_lost; i++)
  {
    V2f spawn_pos(position.x - RAND_BETWEEN(24, 48),
                  position.y + RAND_BETWEEN(-16, 16));
    context->addThing(new EffectThing(spawn_pos, orb_die, 0.1f));
  }
}
