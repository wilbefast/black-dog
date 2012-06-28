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
#ifndef ANIMATEDELEMENT_HPP_INCLUDED
#define ANIMATEDELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../graphics/AnimationIncarnation.hpp"

class AnimatedElement : public ThingElement, public AnimationIncarnation
{
  /// METHODS
public:
  // contructors, destructors
  AnimatedElement(Thing* init_owner, V2f size = V2f(0.0f, 0.0f),
                                    V2f offset = V2f(0.0f, 0.0f),
                                    char flags = CENTER_X|CENTER_Y);
  ~AnimatedElement();

  // overrides
  int update(GameState* context, float delta);     // ThingElement
  void draw();                                    // ThingElement

protected:
  void animEnd();                     // AnimationIncarnation
};

#endif // ANIMATEDELEMENT_HPP_INCLUDED
