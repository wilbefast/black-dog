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
#include "GraphicIncarnation.hpp"

// Constructors, destructors

GraphicIncarnation::GraphicIncarnation(V2f _size, V2f _offset, char _flags) :
sprite(NULL),
destination(size),
offset(_offset),
size(_size),
angle(0),
flags(_flags),
hidden(false)
{
}

GraphicIncarnation::~GraphicIncarnation()
{
    // NB - the sprite is NOT freed as it may in use elsewhere
}

/// QUERY

bool GraphicIncarnation::isSprite(Graphic* check_sprite) const
{
  return (sprite == check_sprite);
}

/// MODIFICATION

void GraphicIncarnation::setAngle(float new_angle)
{
    angle = new_angle;
}

bool GraphicIncarnation::setSprite(Graphic* new_sprite)
{
  // Break if sprite is the same as before
  if(sprite == new_sprite)
      return false;

  // Reset everything only if a new Graphic has been selected
  sprite = new_sprite;
  if(!size)
    size = sprite->getFrame().getSize();
  if(flags & CENTER_X)
    offset.x = -size.x/2.0f;
  if(flags & CENTER_Y)
    offset.y = -size.y/2.0f;

  // Maintain aspect ratio (stretch evenly along)
  destination.setSize(size);
  destination.setRatio(((fRect)sprite->getFrame()).getRatio());

  // Graphic was indeed changed
  return true;
}

void GraphicIncarnation::setHidden(bool _hidden)
{
  hidden = _hidden;
}

void GraphicIncarnation::setPosition(V2f _position)
{
  destination.setPosition(_position + offset);
}

void GraphicIncarnation::draw()
{
  // Break immediately if invisible or nothing has been initialised
  if(hidden || !sprite)
    return;

  // Get the source rectangle by cutting out the appropriate frame
  static fRect source;
  source = sprite->getFrame();

  // Draw the graphic
  sprite->getTexture()->draw(&source, &destination, angle);
}

void GraphicIncarnation::setOffset(V2f _offset)
{
  if(flags & CENTER_X)
    offset.x = _offset.x - size.x/2.0f;
  if(flags & CENTER_Y)
    offset.y = _offset.y - size.y/2.0f;
}

void GraphicIncarnation::setSize(V2f _size)
{
  size = _size;
}
