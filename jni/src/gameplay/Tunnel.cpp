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
#include "Tunnel.hpp"

#include "../graphics/draw.hpp"

/// CREATION AND DESTRUCTION

Tunnel::Tunnel(float _speed_x) :
head_i(0),
offset_x(0),
// speed depends on screen size
speed_x(_speed_x),
// polygon triangles cache
mesh_above(N_PTS, SEGMENT_L, BASE_ABOVE),
mesh_below(N_PTS, SEGMENT_L, BASE_BELOW)
{
  // initialise height maps
  for (int i = 0; i < N_PTS; i++)
  {
    above[i] = MIN_H;
    below[i] = MAX_H;
  }
}


/// LOOP

void Tunnel::update(float delta)
{
  // move the tunnel along towards the left
  offset_x -= speed_x*delta;

  // lap around left to right if offset is larger than segment length
  if (offset_x <= -Tunnel::SEGMENT_L)
  {
    offset_x = 0;
    // cycle the circular array pointer
    head_i = (head_i + 1) % N_PTS;
    // generate new height values
    new_height(head_i);
    // update meshes with new value (triangulate new segments)
    mesh_above.add(above[head_i]);
    mesh_below.add(below[head_i]);
  }
}

void Tunnel::draw()
{
  // override me !
}


/// QUERY

V2i Tunnel::collidingPoint(V2f position) const
{
  // local variables
  V2i collision(0, 0);

  // check collisions with roof
  collision.y = position.y - x_to_height(position.x, above);
  if (collision.y < 0)
  {
    // collision above
    collision.x = (x_to_slope(position.x, above) < 0.0f) ? 1 : -1;
    return collision;
  }

  // check collisions with floor
  collision.y = position.y - x_to_height(position.x, below);
  if(collision.y > 0)
  {
    // collision below
    collision.x = (x_to_slope(position.x, below) < 0.0f) ? 1 : -1;
    return collision;
  }

  // no collision
  return V2i(0, 0);
}

V2i Tunnel::collidingRect(fRect hitbox) const
{
  // local variables
  V2i collision(0, 0);

  // check collisions with roof
  collision = collidingPoint(V2f(hitbox.x + hitbox.w/2, hitbox.y));
  if(collision)
    // collision above
    return collision;

  // check collisions with roof
  if(collidingPoint(V2f(hitbox.x + hitbox.w/2, hitbox.y + hitbox.h)))
    // collision below
    return collision;

  // no collision
  return V2i(0, 0);
}


/// SUB-ROUTINES

void Tunnel::new_height(unsigned int i)
{
  // override me!
}

float Tunnel::index_to_x(unsigned int i) const
{
  int index_diff = (head_i < i) ? i - head_i : N_PTS - head_i + i;
  return (index_diff - 1) * SEGMENT_L + offset_x;
}

int Tunnel::x_to_index(float x, const float hmap[]) const
{
  return ((int) ((x - offset_x) / SEGMENT_L) + 1 + head_i) % N_PTS;
}

float Tunnel::x_to_height(float x, const float hmap[]) const
{
  // array index of point before x
  int start_i = x_to_index(x, hmap),
  // array index of point after x
  end_i = (start_i + 1) % N_PTS;
  // distance between previous point and x
  float dx = x - index_to_x(start_i),
  // slope of the line
  slope = (hmap[end_i] - hmap[start_i]) / SEGMENT_L;

  return dx * slope + hmap[start_i];
}

float Tunnel::x_to_slope(float x, const float hmap[]) const
{
  // array index of point before x
  int start_i = x_to_index(x, hmap),
  // array index of point after x
  end_i = (start_i + 1) % N_PTS;
  // return the slope
  return (hmap[end_i] - hmap[start_i]) / SEGMENT_L;
}
