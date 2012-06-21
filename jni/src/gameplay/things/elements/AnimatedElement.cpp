#include <stdlib.h>

#include "AnimatedElement.hpp"
#include "../events/ThingEvent.hpp"       // for animation_end event

// Constructors, destructors

AnimatedElement::AnimatedElement(Thing* init_owner, V2f size, V2f offset,
                                char flags) :
ThingElement(init_owner),
AnimationIncarnation(size, offset, flags)
{
}

AnimatedElement::~AnimatedElement()
{
}


int AnimatedElement::update(GameState* context, float delta)
{
  // Animate
  frame_current += frame_speed*delta;
  loopAnim();

  // Move destination rectangle to position of object
  destination.setPosition(owner->getPosition() + offset);

  // No interruption
  return SceneState::CONTINUE;
}

void AnimatedElement::draw()
{
  AnimationIncarnation::draw();
}

void AnimatedElement::animEnd()
{
  owner->addEvent(new ThingEvent("animation_end"));
}
