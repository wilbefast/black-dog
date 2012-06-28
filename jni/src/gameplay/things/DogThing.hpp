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
#ifndef DOGTHING_HPP_INCLUDED
#define DOGTHING_HPP_INCLUDED

#include "elements/AnimatedElement.hpp"

class DogThing : public Thing
{
  /// CONSTANTS
private:
  static const int DEATH_THRESHOLD = 32;
  static const int DANGER_THRESHOLD = DEATH_THRESHOLD*4;
  static const int SAFETY_THRESHOLD = DANGER_THRESHOLD*1.1f;

  /// NESTING
private:
  enum State { OFFSCREEN, ARRIVE, IDLE, EAT, LEAVE };

  /// ATTRIBUTES
private:
  AnimatedElement graphic;
  State state;

  /// METHODS
public:
  // creation, destruction
  DogThing(V2i _position);
  // overrides Thing
  int update(GameState*, float delta);
  void draw();

  /// SUBROUTINES
private:
  void setState(State new_state);
  int treatEvent(ThingEvent* event);
};

#endif // DOGTHING_HPP_INCLUDED
