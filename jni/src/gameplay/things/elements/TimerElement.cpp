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
#include "TimerElement.hpp"

TimerElement::TimerElement(Thing* _owner, const char* _name, float init_time) :
ThingElement(_owner),
name(numerise(_name)),
remaining_time(init_time < 0.0f ? 0.0f : init_time)
{
}

float TimerElement::check() const
{
  return remaining_time;
}

bool TimerElement::ticking() const
{
  return (remaining_time >= 0.0f);
}

void TimerElement::set(float time)
{
  remaining_time = time;
}

void TimerElement::unset()
{
  remaining_time = -1.0f;
}

void TimerElement::decrement(float delta)
{
  if(remaining_time < 0.0f)
    return;

  // decrement timer
  if(remaining_time > delta)
    remaining_time -= delta;
  else
  {
    owner->addEvent(new ThingEvent(name));
    remaining_time = -1.0f;
  }
}
