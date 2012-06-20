#include "DogThing.hpp"

#include "../../resources/AudioManager.hpp"
#include "../../resources/GraphicsManager.hpp"

/// CREATION, DESTRUCTION

DogThing::DogThing(V2i _position) :
Thing(_position, "dog"),
graphic(this, V2f(0,0), V2f(0, 0), GraphicElement::CENTER_Y), // don't center horizontally
state(OFFSCREEN)
{
}


/// OVERRIDES THING

int DogThing::update(GameState* context)
{
  // local variables
  V2f hero_position = context->getHero()->getPosition();
  int result = GameState::CONTINUE;

  // mirror the hero's vertical position
  position.y = hero_position.y;

  // death if at the left-hand side of the screen
  if(hero_position.x < DEATH_THRESHOLD)
  {
    setState(EAT);
    context->getHero()->addEvent(new ThingEvent("death"));
  }

  // warn of danger if too far to the left of the screen
  else if(hero_position.x < DANGER_THRESHOLD && state == OFFSCREEN)
    setState(ARRIVE);

  // stop warning if far enough from the left of the screen
  else if(hero_position.x >= SAFETY_THRESHOLD && state != LEAVE && state != OFFSCREEN)
    setState(LEAVE);

  // animate the sprite
  graphic.update(context);

  // treat events last of all, as they will be cleared by Thing::update
  for(EventIter i = events.begin();
      result == GameState::CONTINUE && i != events.end(); i++)
    result = treatEvent(*i);
  if(result != GameState::CONTINUE)
    return result;

  // nothing interrupted execution, so continue looping
  return Thing::update(context);
}

void DogThing::draw()
{
  // draw the sprite
  if(state != OFFSCREEN)
    graphic.draw();
}



/// SUBROUTINES

int DogThing::treatEvent(ThingEvent* event)
{
  static str_id ANIMATION_END = numerise("animation_end");

  if(event->getType() == ANIMATION_END)
  {
    switch(state)
    {
      case ARRIVE:
        setState(IDLE);
      break;

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
    *dog_bite = GraphicsManager::getInstance()->get_animation("dog_bite");

  switch(new_state)
  {
    case ARRIVE:
      AudioManager::getInstance()->play_sound("slime");
      graphic.setSprite(dog_spawn, 0.1f);
    break;

    case LEAVE:
      AudioManager::getInstance()->play_sound("slime");
      graphic.setSprite(dog_spawn, -0.1f);
    break;

    case EAT:
      graphic.setSprite(dog_bite, 0.0f);
    break;

    case IDLE:
      graphic.setSprite(dog_idle, 0.1f);
    break;

    case OFFSCREEN:
    break;
  }

  // set to the new state
  state = new_state;
}
