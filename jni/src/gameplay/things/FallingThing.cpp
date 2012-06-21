#include "FallingThing.hpp"
#include "elements/ColliderElement.hpp"

/// CREATION, DESTRUCTION

FallingThing::FallingThing(V2i _position, const char* name, Animation* loop,
                          float loop_speed, float gravity, float max_speed) :
Thing(_position, name),
graphic(this),
movement(this, max_speed)
{
  graphic.setSprite(loop, loop_speed);
  movement.setSpeed(V2f(-X_SPEED, gravity));
  body = new ColliderElement(this, V2d(V2d(32, 32)));
}


/// OVERRIDES THING

int FallingThing::update(GameState* context, float delta)
{
  // move along
  movement.update(context, delta);

  // animate the sprite
  graphic.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  static str_id out_of_bounds = numerise("out_of_bounds");
  for(EventIter i = events.begin(); i != events.end(); i++)
    if((*i)->getType() == out_of_bounds)
      die();

  // nothing can interrupt execution, so continue looping
  return Thing::update(context, delta);
}

void FallingThing::draw()
{
  // draw the sprite
  graphic.draw();
}

