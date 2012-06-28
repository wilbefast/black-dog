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
#ifndef ANIMATIONINCARNATION_HPP_INCLUDED
#define ANIMATIONINCARNATION_HPP_INCLUDED

#include "GraphicIncarnation.hpp"
#include "Animation.hpp"

// Instance of an animation on the screen (with position, current frame, etc)

class AnimationIncarnation : public GraphicIncarnation
{
  /// ATTRIBUTES
protected:
  float frame_current;
  float frame_speed;

  /// METHODS
public:
  // contructors, destructors
  AnimationIncarnation(V2f size = V2f(0.0f, 0.0f),
                  V2f offset = V2f(0.0f, 0.0f),
                  char flags = CENTER_X|CENTER_Y);
  ~AnimationIncarnation();
  // accessors
  void setFrame(float new_frame);
  void setRandFrame();
  bool setSprite(Animation* new_sprite, float new_speed = 0);
  // modification
  void draw();

  /// SUBROUTINES
protected:
  void loopAnim();
  virtual void animEnd() { } // by default does nothing
};

#endif // ANIMATIONINCARNATION_HPP_INCLUDED
