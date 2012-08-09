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
#ifndef TIMERELEMENT_HPP_INCLUDED
#define TIMERELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../resources/numerise.hpp"     // for str_id

class TimerElement : public ThingElement
{
  /// ATTRIBUTES
private:
  str_id name;
  float remaining_time; // slow machine may perform, say, 1.3 updates rather than 1


  /// METHODS
public:
  TimerElement(Thing* _owner, const char* _name, float init_time = -1.0f);
  // query
  float check() const;
  bool ticking() const;
  // modification
  void set(float time);
  void unset();
  void decrement(float delta);
};

#endif // TIMERELEMENT_HPP_INCLUDED
