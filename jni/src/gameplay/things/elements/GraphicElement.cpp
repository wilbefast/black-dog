#include "GraphicElement.hpp"

// Constructors, destructors

GraphicElement::GraphicElement(Thing* init_owner, V2f _size, V2f _offset) :
ThingElement(init_owner),
sprite(NULL),
destination(size),
offset(_offset),
size(_size),
angle(0)
{
}

GraphicElement::~GraphicElement()
{
    // NB - the sprite is NOT freed as it may in use by other components!
}

// Accessors

void GraphicElement::setAngle(float new_angle)
{
    angle = new_angle;
}

bool GraphicElement::setSprite(Graphic* new_sprite)
{
    // Break if sprite is the same as before
    if(sprite == new_sprite)
        return false;

    // Reset everything only if a new Graphic has been selected
    sprite = new_sprite;
    if(!size)
      size = sprite->getFrame().getSize();
    centreFrame();

    // Graphic was indeed changed
    return true;
}

int GraphicElement::update(GameState* context)
{
    // Move destination rectangle to position of object
    destination.setPosition(owner->getPosition() + offset);

    // No interruption
    return SceneState::CONTINUE;
}

void GraphicElement::draw()
{
    // Get the source rectangle by cutting out the appropriate frame
    static fRect source;
    source = sprite->getFrame();

    // Draw the graphic
    sprite->getTexture()->draw(&source, &destination, angle);
}

// Subroutines

void GraphicElement::centreFrame()
{
    // Centre it
    offset = -size/2.0f;

    destination = fRect(owner->getPosition() + offset, size);
    // Maintain aspect ratio (stretch evenly along)
    destination.setRatio(((fRect)sprite->getFrame()).getRatio());
}

