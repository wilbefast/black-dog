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
  if(!hidden)
  {
    frame_current += frame_speed*delta;
    loopAnim();
  }

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
  owner->addEvent(new ThingEvent("animation_end", this));
}
