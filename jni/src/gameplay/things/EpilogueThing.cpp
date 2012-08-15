#include "EpilogueThing.hpp"

#include "../../io/GraphicsManager.hpp"

EpilogueThing::EpilogueThing(V2i _position) :
Thing(_position, "epilogue"),
wraith(this, V2f(48, 96)),
monk(this, V2f(0, 0))
{
  // set initial sprites
  wraith.setSprite(GraphicsManager::getInstance()->
                    get_animation("wraith_transform"), 0.1f);
  monk.setSprite(GraphicsManager::getInstance()->
                    get_animation("monk_spawn"), -0.1f);
  monk.setOffset(V2f(64, 0));
}

int EpilogueThing::update(GameState* context, float delta)
{
  cout << monk.whichFrame() << endl;


  position.x -= 1.0f;

  // update animations
  wraith.update(context, delta);
  monk.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  static str_id animation_end = numerise("animation_end");

  for(EventIter i = events.begin(); i != events.end(); i++)
    if((*i)->getType() == animation_end)
    {

      if((*i)->getSender() == &wraith)
        ;

      else if((*i)->getSender() == &monk)
      {

        monk.setSprite(GraphicsManager::getInstance()->
                    get_animation("pixie"), 0.1f);

        monk.setFrame(0.3f);
        monk.setOffset(V2f(64, 0));
      }
    }
  return GameState::CONTINUE;
}

void EpilogueThing::draw()
{
  wraith.draw();
  monk.draw();
}
