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
#ifndef PIXIETHING_HPP_INCLUDED
#define PIXIETHING_HPP_INCLUDED

#include "Thing.hpp"

#include "elements/AnimatedElement.hpp"
#include "elements/TimerElement.hpp"
#include "../../global.hpp" // for default window size

class PixieThing : public Thing
{
  /// NESTING
private:
  enum State { TEASE, BECKON_ARRIVE, BECKON_LEAVE, BECKON_IDLE };

  /// CONSTANTS
private:
  static const int SIZE = 32,
                  LEAD = 128,
                  ORB_INTERVAL = 200,
                  BECKON_THRESHOLD = WINDOW_DEFAULT_W * 0.7f,
                  MAX_X = WINDOW_DEFAULT_W * 0.8f;

  /// ATTRIBUTES
private:
  AnimatedElement anim_tease, anim_beckon;
  TimerElement orb_timer;
  State state;

  /// METHODS
public:
  // creation, destruction
  PixieThing(V2i _position);
  // overrides Thing
  int update(GameState*, float delta);
  void draw();

  /// SUBROUTINES
private:
  int treatEvent(ThingEvent* event, GameState* context);
  void setState(State _state);
};

#endif // PIXIETHING_HPP_INCLUDED
