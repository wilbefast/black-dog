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
#include "DogThing.hpp"

#include "MinionThing.hpp"

#include "../../scenes/BlackDogState.hpp"

#include "../../io/AudioManager.hpp"
#include "../../io/GraphicsManager.hpp"

#define STR_UNLEASH_TIMER "unleash_timer"

/// CREATION, DESTRUCTION

DogThing::DogThing(V2i _position, float start_difficulty) :
Thing(_position, "dog"),
// don't center animation horizontally
graphic(this, V2f(0,0), V2f(0, 0), GraphicIncarnation::CENTER_Y),
unleash_timer(this, STR_UNLEASH_TIMER),
state(OFFSCREEN)
{
}


/// OVERRIDES THING

int DogThing::update(GameState* context, float delta)
{
  // local variables
  V2f hero_position = context->getHero()->getPosition();
  float difficulty = ((BlackDogState*)context)->getDifficulty();
  int result = GameState::CONTINUE;

  // mirror the hero's vertical position
  position.y = (position.y*9.0f + hero_position.y)/10.0f;

  // destroy the Dog at the end of the game
  if(difficulty < 0.0f && state == OFFSCREEN)
      die();

  // death if at the left-hand side of the screen
  if(hero_position.x < DEATH_THRESHOLD && state != EAT)
  {
    setState(EAT);
    context->getHero()->addEvent(new ThingEvent("death"));
  }

  else if(state == OFFSCREEN)
  {
    // warn of danger if too far to the left of the screen
    if(hero_position.x < DANGER_THRESHOLD
    // unleash minion dogs if too far to the right of the screen
    ||(!unleash_timer.ticking() && difficulty > 0.4f))
      setState(ARRIVE);
  }

  // stop warning if far enough from the left of the screen
  else if(hero_position.x >= SAFETY_THRESHOLD && state == IDLE)
    setState(LEAVE);

  // animate the sprite
  graphic.update(context, delta);

  // update the timer
  if(unleash_timer.ticking())
    unleash_timer.decrement(delta);

  // treat events last of all, as they will be cleared by Thing::update
  for(EventIter i = events.begin();
      result == GameState::CONTINUE && i != events.end(); i++)
    result = treatEvent(*i, context);
  if(result != GameState::CONTINUE)
    return result;

  // nothing interrupted execution, so continue looping
  return Thing::update(context, delta);
}

void DogThing::draw()
{
  // draw the sprite
  if(state != OFFSCREEN)
    graphic.draw();
}



/// SUBROUTINES

int DogThing::treatEvent(ThingEvent* event, GameState* context)
{
  // local variables
  V2f hero_position = context->getHero()->getPosition();
  static str_id ANIMATION_END = numerise("animation_end");

  if(event->getType() == ANIMATION_END)
  {
    switch(state)
    {
      case ARRIVE:
        if(context->getHero()->getPosition().x < DANGER_THRESHOLD)
          setState(IDLE);
        else
          setState(UNLEASH);
      break;

      case UNLEASH:
        unleash_timer.set(UNLEASH_INTERVAL *
          (1.5f - min(1.0f, hero_position.x / (WINDOW_DEFAULT_W * 0.8f))));
        context->addThing(new MinionThing(position));
      case LEAVE:
        setState(OFFSCREEN);
      break;

      case OFFSCREEN:
      case IDLE:
      case EAT:
      break;
    }
  }

  // nothing to report
  return GameState::CONTINUE;
}

void DogThing::setState(State new_state)
{
  // cache animations used by this Thing
  static Animation
    *dog_spawn = GraphicsManager::getInstance()->get_animation("dog_spawn"),
    *dog_idle = GraphicsManager::getInstance()->get_animation("dog_idle"),
    *dog_bite = GraphicsManager::getInstance()->get_animation("dog_bite"),
    *dog_unleash = GraphicsManager::getInstance()->get_animation("dog_unleash");

  switch(new_state)
  {
    case ARRIVE: // dramatic entrance
      AudioManager::getInstance()->play_sound("dog_spawn");
      graphic.setSprite(dog_spawn, 0.1f);
    break;

    case LEAVE: // give up trying to grab player
      AudioManager::getInstance()->play_sound("dog_spawn");
      graphic.setSprite(dog_spawn, -0.1f);
    break;

    case EAT: // nom nom nom
      graphic.setSprite(dog_bite, 0.0f);
    break;

    case IDLE: // tongue out, try to grab player
      graphic.setSprite(dog_idle, 0.1f);
    break;

    case UNLEASH: // summon evil doggy minion
      graphic.setSprite(dog_unleash, 0.1f);
      AudioManager::getInstance()->play_sound("minion_spawn");
    break;

    case OFFSCREEN:
    break;
  }

  // set to the new state
  state = new_state;
}
