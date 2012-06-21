#include "PixieThing.hpp"

#include "AngelThing.hpp"   // for player position
#include "FallingThing.hpp" // for orbs

#include "../../scenes/BlackDogState.hpp"
#include "../../resources/GraphicsManager.hpp"

#define STR_ORB_TIMER "orb_timer"

/// CREATION, DESTRUCTION

PixieThing::PixieThing(V2i _position) :
Thing(_position, "pixie"),
graphic(this),
orb_timer(this, STR_ORB_TIMER)
{
  // start animation
  graphic.setSprite(GraphicsManager::getInstance()->get_animation("pixie"), 0.1f);

  // start timer
  orb_timer.set(ORB_INTERVAL);
}


/// OVERRIDES THING

int PixieThing::update(GameState* context, float delta)
{
  // local variables
  float player_progress = ((AngelThing*)context->getHero())->getFurthestX();
  const TunnelFG* obstacle = ((BlackDogState*)context)->getObstacle();

  // work out where the exact middle of the tunnel should be
  float desired_x = player_progress + LEAD;

  // don't move past maximum
  if(desired_x > MAX_X)
    position = V2f(MAX_X, obstacle->x_to_middle(MAX_X));
  // move gradually towards the desired position, not all at once
  else
  {
    position.x = (position.x*19.0f + desired_x)/20.0f;
    position.y = (position.y*9.0f + obstacle->x_to_middle(desired_x))/10.0f;
  }

  // animate the sprite
  graphic.update(context, delta);

  // count down the timer
  orb_timer.decrement(delta);

  // treat events last of all, as they will be cleared by Thing::update
  static str_id orb_timer_id = numerise(STR_ORB_TIMER);
  static Animation* orb = GraphicsManager::getInstance()->get_animation("orb");
  for(EventIter i = events.begin(); i != events.end(); i++)
    if((*i)->getType() == orb_timer_id)
    {
      context->addThing(new FallingThing(position, "orb", orb, 0.1f, 0.2f));
      orb_timer.set(ORB_INTERVAL);
    }

  // nothing can interrupt execution, so continue looping
  return Thing::update(context, delta);
}

void PixieThing::draw()
{
  // draw the sprite
  graphic.draw();
}
