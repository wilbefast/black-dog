#include "Tunnel.hpp"

#include "../global.hpp"
#include "../graphics/draw.hpp"

/// CREATION AND DESTRUCTION

Tunnel::Tunnel(float base_speed) :
// 'pseudo-constants'
MIN_H(global::viewport.h / WINDOW_DEFAULT_H * DEFAULT_MIN_H),
MAX_H(global::viewport.h - MIN_H),
SEGMENT_L(global::viewport.w / (N_PTS-2)),
head_i(0),
// speed depends on screen size
speed_x(global::viewport.w / WINDOW_DEFAULT_W * base_speed)
{
  // initialise height maps
  for (int i = 0; i < N_PTS; i++)
  {
    above[i] = MIN_H;
    below[i] = MAX_H;
  }
}


/// LOOP

void Tunnel::update()
{
  // move the tunnel along towards the left
  offset_x -= speed_x;

  // lap around left to right if offset is larger than segment length
  if (offset_x <= -SEGMENT_L)
  {
    offset_x = 0;
    // cycle the circular array pointer
    head_i = (head_i + 1) % N_PTS;
    // generate new height values
    new_height(head_i);
  }
}

void Tunnel::draw()
{
  static V2f drawable[N_PTS+2];
  // draw top height-map
  build_drawable(above, 0.0f, drawable);
  draw::line_loop(drawable, N_PTS+2);
  // draw bottom height-map
  build_drawable(below, global::viewport.h, drawable);
  draw::line_loop(drawable, N_PTS+2);
}


/// QUERY

bool Tunnel::collision(V2f& position)
{
  return (x_to_height(position.x, above) > position.y
      || x_to_height(position.x, below) < position.y);
}


/// SUB-ROUTINES

void Tunnel::new_height(unsigned int i)
{
  // override me!
}

float Tunnel::index_to_x(unsigned int i)
{
  int index_diff = (head_i < i) ? i - head_i : N_PTS - head_i + i;
  return (index_diff - 1) * SEGMENT_L + offset_x;
}

float Tunnel::x_to_height(float x, float hmap[])
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

void Tunnel::build_drawable(float h_map[], float base_y, V2f result[])
{
  // result should be an array N_PTS+2 (start and end) in size
  // result i keeps track of position in result array
  int r_i = 0;
  // move to top-left or bottom-right respectively
  result[r_i++] = V2f(offset_x, base_y);
  // x keeps track of the position on the screen
  float x = offset_x;
  // i keeps track of the position in the height-map (circular array)
  for(unsigned int i = (head_i+1)%N_PTS; i != head_i; i = (i+1)%N_PTS)
  {
    result[r_i++] = V2f(x, h_map[i]);
    x += SEGMENT_L;
  }
  // close off the polygon
  result[r_i++] = V2f(x, h_map[head_i]);
  result[r_i] = V2f(x, base_y);
}
