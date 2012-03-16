#include "TunnelBG.hpp"

#include "../global.hpp"
#include "../wjd_math.hpp"

/// CONSTANTS

draw::Colour TunnelBG::COLOUR_FILL(115, 6, 15);   // dark red


/// CONSTRUCTION AND DESTRUCTION

TunnelBG::TunnelBG() :
Tunnel(DEFAULT_SPEED)
{
    // randomise initial values
		for (int i = 0; i < N_PTS; i++)
			new_height(i);
}

/// OVERRIDES

void TunnelBG::draw()
{
  draw::height_fill(above, N_PTS, SEGMENT_L, V2f(offset_x, 0.0f),
                    head_i, COLOUR_FILL);
  draw::height_fill(below, N_PTS, SEGMENT_L, V2f(offset_x, global::viewport.h),
                    head_i, COLOUR_FILL);
}

void TunnelBG::new_height(unsigned int i)
{
  float middle_h = global::viewport.h/2;
  above[i] = RAND_BETWEEN(MIN_H, middle_h);
  if(above[i] > middle_h)
    cout << "squeal!" << endl;
  below[i] = RAND_BETWEEN(middle_h, MAX_H);
  if(below[i] < middle_h)
    cout << "squeal!" << endl;
}
