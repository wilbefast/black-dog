#include "DogThing.hpp"

#include "../../resources/AudioManager.hpp"
#include "../../resources/GraphicsManager.hpp"

/// CREATION, DESTRUCTION

DogThing::DogThing(V2i _position) :
Thing(_position, "dog"),
graphic(this)
{
  // set initial sprite
  graphic.setSprite(GraphicsManager::getInstance()->
                    get_animation("dog_spawn"), 0.1f);

}


/// OVERRIDES THING

int DogThing::update(GameState* context)
{
  // mirror the hero's vertical position
  //position.y = context->getHero()->getPosition().y;

  // animate the sprite
  graphic.update(context);

  // nothing interrupted execution, so continue looping
  return Thing::update(context);
}

void DogThing::draw()
{
  // draw the sprite
  graphic.draw();
}
