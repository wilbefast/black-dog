#include "GraphicElement.hpp"

/// CREATION, DESTRUCTION

GraphicElement::GraphicElement(Thing* init_owner, V2f _size, V2f _offset, char _flags) :
ThingElement(init_owner),
GraphicIncarnation(_size, _offset, _flags)
{
}

GraphicElement::~GraphicElement()
{
}


/// OVERRIDES

int GraphicElement::update(GameState* context, float delta)
{
  // Move destination rectangle to position of object
  destination.setPosition(owner->getPosition() + offset);

  // No interruption
  return SceneState::CONTINUE;
}

void GraphicElement::draw()
{
  GraphicIncarnation::draw();
}
