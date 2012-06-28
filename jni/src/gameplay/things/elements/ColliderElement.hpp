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
#ifndef COLLIDERELEMENT_HPP_INCLUDED
#define COLLIDERELEMENT_HPP_INCLUDED

class ColliderElement;

#include "ThingElement.hpp"
#include "../../../math/Rect.hpp"

class ColliderElement : public ThingElement
{
    /// ATTRIBUTES
    private:
    fRect hitbox;

    /// METHODS
    public:
    // constructors, destructors
    ColliderElement(Thing* init_owner, V2f size, V2f offset = V2f(0,0));
    ColliderElement(const ColliderElement& src);
    // main methods
    bool isColliding(ColliderElement* other, V2i* side = NULL) const;
    bool isOutside(fRect* bounds, V2i* side = NULL) const;
    bool isLeaving(fRect* bounds, V2i* side = NULL) const;
    bool doesContain(V2f point) const;
    // accessors
    fRect getOffsetBox() const;
    V2i boundarySide(fRect* bounds) const;
    V2i collisionSide(ColliderElement* other) const;

};

#endif // COLLIDERELEMENT_HPP_INCLUDED
