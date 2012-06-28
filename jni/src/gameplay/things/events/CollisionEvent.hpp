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
#ifndef COLLISIONEVENT_HPP_INCLUDED
#define COLLISIONEVENT_HPP_INCLUDED

#include "ThingEvent.hpp"
#include "../Thing.hpp"

class CollisionEvent : public ThingEvent
{
    /// FUNCTIONS
    public:
    static void generate(Thing* a, Thing* b);

    /// ATTRIBUTES
    private:
    Thing* other;
    V2i collision_side;

    /// METHODS
    public:
    // constructors, destructor
    CollisionEvent(Thing* other, V2i side);
    // accessors
    Thing* getOther();
    V2i getSide() const;
};

#endif // COLLISIONEVENT_HPP_INCLUDED
