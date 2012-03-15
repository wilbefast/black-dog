#include "GraphicElement.hpp"
#include "../../../global.hpp"               // for scaling images

// Constructors, destructors

GraphicElement::GraphicElement(Thing* init_owner) :
ThingElement(init_owner),
sprite(NULL),
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
    // Use the full frame size
    V2f frame_size = sprite->getFrame().getSize();

    // Stretch it to be the correct size relative to the screen
    static V2f normaliser(WINDOW_DEFAULT_W, WINDOW_DEFAULT_H);
    frame_size *= (V2f)global::viewport.getSize() / normaliser;

    // Centre it
    offset = -frame_size/2.0f;
    destination = fRect(owner->getPosition() + offset, frame_size);

    // Maintain aspect ratio (stretch evenly along)
    destination.setRatio(sprite->getFrame().getRatio());
}

