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
#include "TunnelFG.hpp"

/// CONSTANTS

draw::Colour TunnelFG::COLOUR_FILL(242, 68, 5);  // orange
draw::Colour TunnelFG::COLOUR_LINE(44, 0, 0);    // very dark red
const float TunnelFG::MAX_DELTA = WINDOW_DEFAULT_H / 2.5f;

/// CREATION AND DESTRUCTION

TunnelFG::TunnelFG(float start_difficulty) :
Tunnel(DEFAULT_SPEED),
difficulty(start_difficulty)
{
  // randomise initial values
  for (int i = 0; i < N_PTS; i++)
  {
    middle_y[i] = WINDOW_DEFAULT_H / 2;
    new_height(i);
  }

  // generate initial meshes (triangulate polygons defined by height maps)
  mesh_above.bake(above);
  mesh_below.bake(below);
}

float TunnelFG::x_to_middle(float x) const
{
  return x_to_height(x, middle_y);
}

void TunnelFG::setDifficulty(float _difficulty)
{
  if(_difficulty >= 0.0f && _difficulty <= 1.0f)
    difficulty = _difficulty;
}


/// OVERRIDES

void TunnelFG::draw()
{
  // draw the roof of the cavern
  mesh_above.draw(offset_x, COLOUR_FILL);
  draw::height_line(above, N_PTS, SEGMENT_L, V2f(offset_x, 0.0f),
                    head_i, COLOUR_LINE, 1.7f);

  // draw the floor
  mesh_below.draw(offset_x, COLOUR_FILL);
  draw::height_line(below, N_PTS, SEGMENT_L, V2f(offset_x, 0.0f),
                    head_i, COLOUR_LINE, 1.7f);
}

void TunnelFG::new_height(unsigned int i)
{
  // change in height this time around
  float delta = MAX_DELTA * difficulty;
  // lower bound for new point
  float lower;
  // upper bound for new point
  float upper;
  float girth = (float) MAX(MIN_GIRTH, BASE_GIRTH * (1.0 - difficulty));

  // change middle
  lower = MAX(MIN_H + girth/2, middle_y[i] - delta);
  upper = MIN(MAX_H - girth/2, middle_y[i] + delta);
  middle_y[i] = RAND_BETWEEN(lower, upper);

  // avoid sharp changes!
  int prev_i = (i == 0) ? (N_PTS - 1) : i - 1;
  double prev_above = above[prev_i], prev_below = below[prev_i];

  // change top
  lower = MAX(MIN_H, prev_above - delta);
  upper = MIN(prev_above + delta, middle_y[i] - girth / 2);
  above[i] = RAND_BETWEEN(lower, upper);

  // change bottom
  lower = MAX(middle_y[i] + girth / 2, prev_below - delta);
  upper = MIN(MAX_H, prev_below + delta);
  below[i] = RAND_BETWEEN(lower, upper);
}
