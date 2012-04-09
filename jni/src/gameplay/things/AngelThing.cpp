#include "AngelThing.hpp"

#include "../../resources/GraphicsManager.hpp"

/// PLAYER STATES

unsigned int AngelThing::State::next_id = 0;

AngelThing::State::State(float _gravity, float _max_speed) :
gravity(_gravity), max_speed(_max_speed), id(State::next_id)
{
  AngelThing::State::next_id++;
}

bool AngelThing::State::operator==(const AngelThing::State& other) const
{
  return (id == other.id);
}

AngelThing::State AngelThing::FLAPPING(0.2f, 2.0f);
AngelThing::State AngelThing::GLIDING(0.1f, 0.7f);
AngelThing::State AngelThing::FALLING(0.4f, 10.0f);
AngelThing::State AngelThing::STUNNED(0.3f, 5.0f);
AngelThing::State AngelThing::DEAD(1.0f, 0.0f);



/// CONSTRUCTION & DESTRUCTION

AngelThing::AngelThing(V2i _position) :
Thing(_position, "angel"),
state(FALLING),
graphic(this, V2f(SPRITE_DEFAULT_W, SPRITE_DEFAULT_H)),
//thrust(this, SPEED_MAX, FRICTION),
feathers(this, INIT_FEATHERS)
{
  // set initial sprite
  Animation* wraith = GraphicsManager::getInstance()->get_animation("wraith");
  graphic.setSprite(wraith, 0.1f);

  // angel is collideable
  //body = new ColliderElement(this, V2d(V2d(HITBOX_W, HITBOX_H)));
}

/// OVERRIDES

void AngelThing::draw()
{
  // draw the sprite
  graphic.draw();
}

int AngelThing::update(GameState* context)
{
  // animate the sprite
  graphic.update(context);

  // nothing interrupted execution, so continue looping
  return Thing::update(context);
}
