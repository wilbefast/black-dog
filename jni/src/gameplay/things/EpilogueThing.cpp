#include "EpilogueThing.hpp"

#include "../../io/GraphicsManager.hpp"

#include "../../scenes/BlackDogState.hpp"

#include "../../global.hpp"

EpilogueThing::EpilogueThing(V2i _position) :
Thing(_position, "epilogue"),
wraith(this, V2f(48, 96)),
monk(this, V2f(0, 0)),
act(0)
{
  // set initial sprites
  wraith.setSprite(GraphicsManager::getInstance()->
                    get_animation("wraith_transform"), 0.08f);
  monk.setSprite(GraphicsManager::getInstance()->
                    get_animation("monk_spawn"), -0.08f);
  monk.setOffset(V2f(64, 0));
}

int EpilogueThing::update(GameState* context, float delta)
{
  // move backwards or forwards horizontally
  static float speed_x = -3.0f;
  position.x += speed_x;
  if(act == 2)
  {
    speed_x = (speed_x < 1.5f) ? speed_x + 0.05f : 1.5f;
    if(position.x > WINDOW_DEFAULT_W * 1.2)
      return GameState::WIN_LEVEL;
  }

  // update animations
  wraith.update(context, delta);
  monk.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  if(act < 2)
  {
    for(EventIter i = events.begin(); i != events.end(); i++)
    {
      if((*i)->getSender() == &wraith)
      {
        wraith.setSprite(GraphicsManager::getInstance()->
              get_animation("wraith_orb"), 0.1f);
        wraith.setOffset(V2f(0, 30));
        wraith.update(context, 0.0f); // pseudo-update to get frame in right place
        act++;
      }
      else if((*i)->getSender() == &monk)
      {

        monk.setSprite(GraphicsManager::getInstance()->
                    get_animation("pixie"), 0.1f);
        monk.setSize(V2f(32, 32));
        monk.setOffset(V2f(64, 0));
        act++;
      }
      else
        continue;

      if(act == 2)
        ((BlackDogState*)context)->openTunnel();
    }
  }
  return Thing::update(context, delta);
}

void EpilogueThing::draw()
{
  wraith.draw();
  monk.draw();
}
