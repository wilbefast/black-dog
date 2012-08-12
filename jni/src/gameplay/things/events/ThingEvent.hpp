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
#ifndef THINGEVENT_HPP_INCLUDED
#define THINGEVENT_HPP_INCLUDED

#include <iostream>     // for std::ostream
#include <list>

#include "../../../math/numerise.hpp"

class ThingEvent;

typedef std::list<ThingEvent*> EventList;
typedef EventList::iterator EventIter;
typedef EventList::const_iterator ConstEventIter;

class ThingEvent
{
    /// ATTRIBUTES
    private:
    str_id type;   // hash
    void* sender;

    /// METHODS
    public:
    // constructors, destructors
    ThingEvent(const char* init_type_name, void* _sender = NULL);
    ThingEvent(str_id init_type_name, void* sender = NULL);
    // accessors
    void* getSender() const;
    str_id getType() const;
    bool isType(const char* type_name) const;

    // outstream operator
    void print(std::ostream& stream) const;
};

std::ostream& operator<<(std::ostream& stream, ThingEvent const& e);

#endif // THINGEVENT_HPP_INCLUDED
