/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MinionThing.hpp"

#include "FallingThing.hpp"

#include "elements/ColliderElement.hpp"

#include "../../resources/GraphicsManager.hpp"

MinionThing::MinionThing(V2i _position) :
Thing(_position, "minion"),
dying(false),
graphic(this, V2f(64, 36)),
movement(this, 2.0f)
{
  // set initial sprite
  graphic.setSprite(GraphicsManager::getInstance()->
                    get_animation("minion"), 0.1f);

  // set initial speed
  movement.setSpeedX(2.0f);

  // create body
  body = new ColliderElement(this, V2d(V2d(32, 16)));
}

void MinionThing::draw()
{
  graphic.draw();
}

int MinionThing::update(GameState* context, float delta)
{
  if(!dying)
  {
    V2f hero_pos = context->getHero()->getPosition();

    // home in on player
    if(hero_pos.y > position.y + 1.0f)
      movement.addSpeedY(0.01f);
    else if(hero_pos.y < position.y - 1.0f)
      movement.addSpeedY(-0.01f);

    // die if past player
    if(position.x > hero_pos.x + 96.0f)
    {
      graphic.setSprite(GraphicsManager::getInstance()->
                    get_animation("minion_die"), 0.1f);
      movement.setSpeed(V2f(1.0f, 0.0f));
      dying = true;
    }
  }

  // update elements
  movement.update(context, delta);
  graphic.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  static str_id out_of_bounds = numerise("out_of_bounds"),
                animation_end = numerise("animation_end");
  for(EventIter i = events.begin(); i != events.end(); i++)
  {
    if(dying && (*i)->getType() == animation_end)
    {
      // create the imps
      static Animation* imp = GraphicsManager::getInstance()->get_animation("imp");
      for(unsigned int i = 0; i < 3; i++)
      {
        V2f spawn_pos(position.x + RAND_BETWEEN(-4,4), position.y - 16 + 16*i);
        context->addThing(new FallingThing(spawn_pos, "imp", imp , 0.15f, 0.0f));
      }
      die();
    }
    else if((*i)->getType() == out_of_bounds)
      die();
  }

  return Thing::update(context, delta);;
}
