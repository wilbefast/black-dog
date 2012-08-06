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
#include "FallingThing.hpp"
#include "elements/ColliderElement.hpp"

const float FallingThing::X_SPEED = 3.0f;

/// CREATION, DESTRUCTION

FallingThing::FallingThing(V2i _position, const char* name, Animation* loop,
                          float loop_speed, float gravity, float max_speed) :
Thing(_position, name),
graphic(this),
movement(this, max_speed)
{
  graphic.setSprite(loop, loop_speed);
  graphic.setRandFrame();
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

