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
#include "PixieThing.hpp"

#include "AngelThing.hpp"   // for player position
#include "FallingThing.hpp" // for orbs

#include "../../scenes/BlackDogState.hpp"
#include "../../io/GraphicsManager.hpp"

#include "../../math/V2.hpp"

#define STR_ORB_TIMER "orb_timer"

/// CREATION, DESTRUCTION

PixieThing::PixieThing(V2i _position) :
Thing(_position, "pixie"),
anim_tease(this),
// don't center animation horizontally
anim_beckon(this, V2f(0,0), V2f(-10, 0), GraphicIncarnation::CENTER_Y),
orb_timer(this, STR_ORB_TIMER),
state(TEASE)
{
  // start animation
  anim_tease.setSprite(GraphicsManager::getInstance()->get_animation("pixie"),
                                                                        0.1f);
  anim_beckon.setSprite(GraphicsManager::getInstance()->get_animation("monk_idle"),
                                                                        0.1f);
  anim_beckon.setHidden(true);

  // start timer
  orb_timer.set(ORB_INTERVAL);
}


/// OVERRIDES THING

int PixieThing::update(GameState* context, float delta)
{
  // local variables
  float player_progress = ((AngelThing*)context->getHero())->getFurthestX();
  V2f player_pos = ((AngelThing*)context->getHero())->getPosition();
  const TunnelFG* obstacle = ((BlackDogState*)context)->getObstacle();
  int result = GameState::CONTINUE;

  // work out where we want to be (in the middle of the tunnel)
  V2f desired(player_progress + LEAD, 0.0f);
  if(desired.x > MAX_X)
    desired.x = MAX_X;
  desired.y = (player_pos.x > BECKON_THRESHOLD)
                ? player_pos.y
                : obstacle->x_to_middle(desired.x);

  // move gradually towards the desired position, not all at once
  position.x = (position.x*19.0f + desired.x)/20.0f;
  position.y = (position.y*9.0f + desired.y)/10.0f;

  // state transition
  if(state == TEASE && player_pos.x > BECKON_THRESHOLD)
    setState(BECKON_ARRIVE);
  else if(state == BECKON_IDLE && player_pos.x <= BECKON_THRESHOLD)
    setState(BECKON_LEAVE);

  // count down the timer
  orb_timer.decrement(delta);

  // animate the sprite
  anim_tease.update(context, delta);
  anim_beckon.update(context, delta);

  // treat events last of all
  for(EventIter i = events.begin();
      result == GameState::CONTINUE && i != events.end(); i++)
    result = treatEvent(*i, context);
  if(result != GameState::CONTINUE)
    return result;

  // nothing can interrupt execution, so continue looping
  return Thing::update(context, delta);
}

void PixieThing::draw()
{
  // draw the sprite
  anim_tease.draw();
  anim_beckon.draw();
}


/// SUBROUTINES

int PixieThing::treatEvent(ThingEvent* event, GameState* context)
{
  static str_id orb_timer_id = numerise(STR_ORB_TIMER);
  static Animation* orb = GraphicsManager::getInstance()->get_animation("orb");
  static str_id animation_end = numerise("animation_end");

  // last frame of an animation
  if(event->getType() == animation_end)
  {
    switch(state)
    {
      case BECKON_ARRIVE:
        setState(BECKON_IDLE);
      break;

      case BECKON_LEAVE:
        setState(TEASE);
      break;

      case TEASE:
      case BECKON_IDLE:
      break;
    }
  }
  // time to spawn a new orb
  else if(event->getType() == orb_timer_id)
  {
    context->addThing(new FallingThing(position, "orb", orb, 0.1f, 0.2f));
    orb_timer.set(ORB_INTERVAL);
  }

  // nothing to report
  return GameState::CONTINUE;
}

void PixieThing::setState(State new_state)
{
  // cache animations used by this Thing
  static Animation
    *monk_spawn = GraphicsManager::getInstance()->get_animation("monk_spawn"),
    *monk_idle = GraphicsManager::getInstance()->get_animation("monk_idle");

  switch(new_state)
  {
    case TEASE:
      anim_beckon.setHidden(true);
      anim_tease.setHidden(false);
    break;

    case BECKON_ARRIVE:
      anim_beckon.setHidden(false);
      anim_tease.setHidden(true);
      anim_beckon.setSprite(monk_spawn, 0.1f);
    break;

    case BECKON_LEAVE:
      anim_beckon.setSprite(monk_spawn, -0.1f);
    break;

    case BECKON_IDLE:
      anim_beckon.setSprite(monk_idle, 0.1f);
    break;
  }

  // last of all, set the new state
  state = new_state;
}
