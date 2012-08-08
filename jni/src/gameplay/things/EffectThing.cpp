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

#include "EffectThing.hpp"

/// CREATION, DESTRUCTION

EffectThing::EffectThing(V2i _position, Animation* anim, float loop_speed) :
Thing(_position, "effect"),
graphic(this)
{
  graphic.setSprite(anim, loop_speed);
}


/// OVERRIDES THING

int EffectThing::update(GameState* context, float delta)
{
  /// FIXME -- kludge quickfix for "Black Dog" which scrolls right-to-left ;)
  position.x -= 3.0f;

  // animate the sprite
  graphic.update(context, delta);

  // treat events last of all, as they will be cleared by Thing::update
  static str_id animation_end = numerise("animation_end");
  for(EventIter i = events.begin(); i != events.end(); i++)
    if((*i)->getType() == animation_end)
      die();

  // nothing can interrupt execution, so continue looping
  return Thing::update(context, delta);
}

void EffectThing::draw()
{
  // draw the sprite
  graphic.draw();
}
