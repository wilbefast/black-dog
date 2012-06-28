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
#include "TunnelBG.hpp"

#include "../math/wjd_math.hpp"

/// CONSTANTS

draw::Colour TunnelBG::COLOUR_FILL(115, 6, 15);   // dark red


/// CONSTRUCTION AND DESTRUCTION

TunnelBG::TunnelBG() :
Tunnel(DEFAULT_SPEED)
{
    // randomise initial values
		for (int i = 0; i < N_PTS; i++)
			new_height(i);

    // generate initial meshes (triangulate polygons defined by height maps)
    mesh_above.bake(above);
    mesh_below.bake(below);
}

/// OVERRIDES

void TunnelBG::draw()
{
  mesh_above.draw(offset_x, COLOUR_FILL);
  mesh_below.draw(offset_x, COLOUR_FILL);
}

void TunnelBG::new_height(unsigned int i)
{
  above[i] = RAND_BETWEEN(MIN_H, (MIN_H+MAX_H)/2);
  below[i] = RAND_BETWEEN((MIN_H+MAX_H)/2, MAX_H);
}
