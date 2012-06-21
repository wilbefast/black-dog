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

int Tunnel::collidingPoint(V2f position) const
{
  if (x_to_height(position.x, above) > position.y)
    // collision above
    return -1;

  else if(x_to_height(position.x, below) < position.y)
    // collision below
    return 1;

  else
    // no collision
    return 0;
}

int Tunnel::collidingRect(fRect hitbox) const
{
  if(collidingPoint(V2f(hitbox.x + hitbox.w/2, hitbox.y)))
    // collision above
    return -1;

  else if(collidingPoint(V2f(hitbox.x + hitbox.w/2, hitbox.y + hitbox.h)))
    // collision below
    return 1;

  else
    // no collision
    return 0;
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

float Tunnel::x_to_height(float x, const float hmap[]) const
{
  // array index of point before x
  int start_i = ((int) ((x - offset_x) / SEGMENT_L) + 1 + head_i) % N_PTS,
  // array index of point after x
  end_i = (start_i + 1) % N_PTS;
  // distance between previous point and x
  float dx = x - index_to_x(start_i),
  // base height for affine function
  base = hmap[start_i],
  // slope of the line
  slope = (hmap[end_i] - base) / SEGMENT_L;

  return dx * slope + base;
}
