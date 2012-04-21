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
