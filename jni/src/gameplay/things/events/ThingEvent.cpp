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
#include "../../../math/numerise.hpp"
#include "ThingEvent.hpp"

using namespace std;


/// CONSTRUCTORS, DESTRUCTORS

ThingEvent::ThingEvent(const char* _type, void* _sender) :
type(numerise(_type)),
sender(_sender)
{
}

ThingEvent::ThingEvent(str_id _type, void* _sender) :
type(_type),
sender(_sender)
{
}


/// ACCESSORS

void* ThingEvent::getSender() const
{
  return sender;
}

str_id ThingEvent::getType() const
{
    return type;
}

bool ThingEvent::isType(const char* name) const
{
    return (type == numerise(name));
}


/// OUTSTREAM OPERATOR
void ThingEvent::print(ostream& stream) const
{
    stream << "ThingEvent " << type;
}

ostream& operator<<(std::ostream& stream, ThingEvent const& e)
{
    e.print(stream);
    return stream;
}
