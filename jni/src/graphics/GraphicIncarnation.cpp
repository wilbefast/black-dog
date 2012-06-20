#include "GraphicIncarnation.hpp"

// Constructors, destructors

GraphicIncarnation::GraphicIncarnation(V2f _size, V2f _offset, char _flags) :
sprite(NULL),
destination(size),
offset(_offset),
size(_size),
angle(0),
flags(_flags)
{
}

GraphicIncarnation::~GraphicIncarnation()
{
    // NB - the sprite is NOT freed as it may in use elsewhere
}

// Accessors

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

void GraphicIncarnation::setPosition(V2f _position)
{
  destination.setPosition(_position + offset);
}

void GraphicIncarnation::draw()
{
  // Break immediately if nothing has been initialised
  if(!sprite)
    return;

  // Get the source rectangle by cutting out the appropriate frame
  static fRect source;
  source = sprite->getFrame();

  // Draw the graphic
  sprite->getTexture()->draw(&source, &destination, angle);
}


