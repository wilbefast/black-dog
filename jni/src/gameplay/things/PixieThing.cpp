#include "PixieThing.hpp"

#include "AngelThing.hpp"

#include "../../scenes/BlackDogState.hpp"
#include "../../resources/GraphicsManager.hpp"

/// CREATION, DESTRUCTION

PixieThing::PixieThing(V2i _position) :
Thing(_position, "pixie"),
graphic(this)
{
  graphic.setSprite(GraphicsManager::getInstance()->get_animation("pixie"), 0.1f);
}


/// OVERRIDES THING

int PixieThing::update(GameState* context)
{
  // local variables
  float player_progress = ((AngelThing*)context->getHero())->getFurthestX();
  const TunnelFG* obstacle = ((BlackDogState*)context)->getObstacle();

  // work out where the exact middle of the tunnel should be
  float desired_x = player_progress + LEAD;
  V2f desired(desired_x, obstacle->x_to_middle(desired_x));

  // move gradually towards the desired position, not all at once
  position.x = desired.x;
  position.y = (9*position.y + 1*desired.y) / 10.0f;

  // animate the sprite
  graphic.update(context);

  // nothing can interrupt execution, so continue looping
  return GameState::CONTINUE;
}

void PixieThing::draw()
{
  // draw the sprite
  graphic.draw();
}
