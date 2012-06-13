#include <stdlib.h>

#include "AnimatedElement.hpp"
#include "../events/ThingEvent.hpp"       // for animation_end event

// Constructors, destructors

AnimatedElement::AnimatedElement(Thing* init_owner, V2f size, V2f offset,
                                char flags) :
GraphicElement(init_owner, size, offset, flags),
frame_current(0),
frame_speed(0)
{
}

AnimatedElement::~AnimatedElement()
{
    // NB - the sprite is NOT freed as it may in use by other components!
}

// Accessors

bool AnimatedElement::setSprite(Animation* new_sprite, float new_speed)
{
  // Standard setting operation
  if(!GraphicElement::setSprite(new_sprite))
      ;
      //return false;
      // NB - removed as speed is not reset if sprite is the same!

  frame_speed = new_speed;
  frame_current = (new_speed >= 0) ? 0 : ((Animation*)sprite)->getNumFrames()-1;
  resetDestination();

  // Graphic was indeed changed
  return true;
}

void AnimatedElement::setFrame(float new_frame)
{
  frame_current = new_frame;
  loopAnim();
}

void AnimatedElement::setRandFrame()
{
  // pick random frame
  frame_current = rand() % ((Animation*)sprite)->getNumFrames();
}

void AnimatedElement::loopAnim()
{
  // Break immediately if nothing has been initialised
  if(!sprite)
    return;

  // Detect if we're over the maximum number of frames
  int frame_number = ((Animation*)sprite)->getNumFrames();

  if(frame_current >= frame_number || frame_current < 0)
  {
      // Loop animation
      frame_current += (frame_current < 0) ? frame_number : -frame_number;
      // Signal animation end
      owner->addEvent(new ThingEvent("animation_end"));
  }
}

int AnimatedElement::update(GameState* context)
{
    // Animate
    frame_current += frame_speed;
    loopAnim();

    // Move destination rectangle to position of object
    destination.setPosition(owner->getPosition() + offset);

    // No interruption
    return SceneState::CONTINUE;
}

void AnimatedElement::draw()
{
  // Break immediately if nothing has been initialised
  if(!sprite)
    return;

  // Get the source rectangle by cutting out the appropriate frame
  static fRect source;
  source = ((Animation*)sprite)->getFrame(frame_current);

  // Draw the graphic
  sprite->getTexture()->draw(&source, &destination, angle);
}
