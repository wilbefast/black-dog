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
#include "events/CollisionEvent.hpp"

#include "../../io/AudioManager.hpp"
#include "../../io/GraphicsManager.hpp"

#include "../../global.hpp" // for WINDOW_DEFAULT_W

MinionThing::MinionThing(V2i _position) :
Thing(_position, "minion"),
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
  // cache animations
  static Animation
    *anim_normal = GraphicsManager::getInstance()->get_animation("minion"),
    *anim_impify = GraphicsManager::getInstance()->get_animation("minion_impify"),
    *anim_die = GraphicsManager::getInstance()->get_animation("minion_die"),
    *anim_imp = GraphicsManager::getInstance()->get_animation("imp");

  // if playing normal animation, state is normal
  if(graphic.isSprite(anim_normal))
  {
    // cache hero position
    V2f hero_pos = context->getHero()->getPosition();

    // home in on player
    if(hero_pos.y > position.y + 1.0f)
      movement.addSpeedY(0.01f);
    else if(hero_pos.y < position.y - 1.0f)
      movement.addSpeedY(-0.01f);

    // die if past player
    if(position.x > hero_pos.x + 96.0f
    // die if too far to the right of the screen
    || position.x > WINDOW_DEFAULT_W - 96.0f)
    {
      graphic.setSprite(anim_impify, 0.1f);
      movement.setSpeed(V2f(1.0f, 0.0f));
    }
  }

  // update elements
  movement.update(context, delta);
  graphic.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  static str_id out_of_bounds = numerise("out_of_bounds"),
                animation_end = numerise("animation_end"),
                collision = numerise("collision");

  for(EventIter i = events.begin(); i != events.end(); i++)
  {
    // if event is "collision" and colliding with the hero
    if((*i)->getType() == collision
    && ((CollisionEvent*)(*i))->getOther() == context->getHero())
    {
      graphic.setSprite(anim_die, 0.1f);
      movement.setSpeed(V2f(0.5f, 0.0f));
    }

    // if event is "animation end"
    else if((*i)->getType() == animation_end)
    {
      // if turning into an imp
      if(graphic.isSprite(anim_impify))
      {
        // create the imps
        for(unsigned int i = 0; i < 3; i++)
        {
          V2f spawn_pos(position.x + RAND_BETWEEN(-4,4), position.y - 16 + 16*i);
          context->addThing(new FallingThing(spawn_pos, "imp", anim_imp , 0.15f, 0.0f));
        }
        AudioManager::getInstance()->play_sound("imp_spawn");
        die();
      }
      // if exploding
      else if(graphic.isSprite(anim_die))
      {
        AudioManager::getInstance()->play_sound("minion_die");
        die();
      }
    }

    // if event is "out of bounds"
    else if((*i)->getType() == out_of_bounds)
      die();
  }

  return Thing::update(context, delta);;
}
