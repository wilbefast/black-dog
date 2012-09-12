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
#include "ColliderElement.hpp"

/// METHODS

// constructors, destructors

ColliderElement::ColliderElement(Thing* init_owner, V2f size, V2f offset) :
ThingElement(init_owner),
hitbox(size)
{
  // Center correctly
  hitbox.setPosition(-hitbox.getSize()/2.0f + offset);
}

// main methods

bool ColliderElement::isColliding(ColliderElement* other, V2i* side) const
{
  // Check for collision between the translated hitboxes
  if(getOffsetBox().doesInter(other->getOffsetBox()))
  {
    // if the collision side is requested
    if(side)
      (*side) = collisionSide(other);

    // either way return true
    return true;
  }
  else
    return false;
}

bool ColliderElement::isOutside(fRect* bounds, V2i* side) const
{
  // Check if the entire translated hitbox is outside the boundary
  if(!bounds->doesInter(getOffsetBox()))
  {
    // if the side we've crossed is requested...
    if(side)
      (*side) = boundarySide(bounds);

    // either way return true
    return true;
  }
  else
    return false;
}

bool ColliderElement::isLeaving(fRect* bounds, V2i* side) const
{
  fRect this_box = getOffsetBox();

  // round to nearest integer to compare
  if ((iRect)(bounds->getInter(this_box)) != (iRect)this_box)
  {
    // if the side we've crossed is requested...
    if(side)
      (*side) = boundarySide(bounds);

    // either way return true
    return true;
  }
  else
    return false;

}

bool ColliderElement::doesContain(V2f point) const
{
  return getOffsetBox().contains(point);
}

// accessors
fRect ColliderElement::getOffsetBox() const
{
  return hitbox + owner->getPosition();
}

V2i ColliderElement::boundarySide(fRect* bounds) const
{
  // local variables
  fRect this_box = getOffsetBox();
  V2f top_left = this_box.getPosition() - bounds->getPosition();
  V2f bottom_right = top_left + this_box.getSize() - bounds->getSize();

  // (0,0) by default, meaning a collision on neither side
  V2i result(0,0);

  // horizontal collision
  if(top_left.x < 0)
    result.x = -1;
  if(bottom_right.x > 0)
    result.x = 1;

  // vertical collision
  if(top_left.y < 0)
    result.y = -1;
  if(bottom_right.y > 0)
    result.y = 1;

  // return the result
  return result;
}

V2i ColliderElement::collisionSide(ColliderElement* other) const
{
  // local variables
  V2f to_target = other->owner->getPosition() - owner->getPosition();

  // (0,0) by default, meaning a collision on neither side
  V2i result(0,0);
  if(abs(to_target.x) - abs(to_target.y) > 0.2)
    result.x = SIGN(to_target.x);
  else if(abs(to_target.x) - abs(to_target.y) < -0.2)
    result.y = SIGN(to_target.y);
  else
    result = to_target.sign();

  // return the result
  return result;
}
