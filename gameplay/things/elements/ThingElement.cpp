#include "ThingElement.hpp"

/// CONSTRUCTORS, DESTRUCTOR

ThingElement::ThingElement(Thing* init_owner) :
owner(init_owner)
{
}

ThingElement::~ThingElement()
{
}

/// OVERRIDDEN

int ThingElement::update(GameState* context)
{
    // overridden if updates
    return SceneState::CONTINUE;
}

void ThingElement::draw()
{
    // overridden if visible
}

