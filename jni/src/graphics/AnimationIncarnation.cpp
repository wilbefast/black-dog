#include "AnimationIncarnation.hpp"

AnimationIncarnation::AnimationIncarnation(V2f size, V2f offset,
                                            char flags) :
GraphicIncarnation(size, offset, flags),
frame_current(0),
frame_speed(0)
{
}

AnimationIncarnation::~AnimationIncarnation()
{
}

// Accessors

bool AnimationIncarnation::setSprite(Animation* new_sprite, float new_speed)
{
  // Standard setting operation
  if(!GraphicIncarnation::setSprite(new_sprite))
      ;
      //return false;
      // NB - removed as speed is not reset if sprite is the same!

  frame_speed = new_speed;
  frame_current = (new_speed >= 0) ? 0 : ((Animation*)sprite)->getNumFrames()-1;

  // Graphic was indeed changed
  return true;
}

void AnimationIncarnation::setFrame(float new_frame)
{
  frame_current = new_frame;
  loopAnim();
}

void AnimationIncarnation::setRandFrame()
{
  // pick random frame
  frame_current = rand() % ((Animation*)sprite)->getNumFrames();
}

void AnimationIncarnation::loopAnim()
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
      animEnd();
  }
}


void AnimationIncarnation::draw()
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

