#include "TunnelFG.hpp"

#include "../global.hpp"

/// CONSTANTS

draw::Colour TunnelFG::COLOUR_FILL(242, 68, 5);  // orange
draw::Colour TunnelFG::COLOUR_LINE(44, 0, 0);    // very dark red

/// CREATION AND DESTRUCTION

TunnelFG::TunnelFG() :
Tunnel(DEFAULT_SPEED),
MIN_GIRTH(global::viewport.h * DEFAULT_MIN_GIRTH / WINDOW_DEFAULT_H ),
BASE_GIRTH(global::viewport.h / 3.0f),
MAX_DELTA(global::viewport.h / 2.0f),
middle_y(global::viewport.h / 2.0f),
difficulty(1.0f)
{
		// randomise initial values -- must be done AFTER pseudo-constants
		for (int i = 0; i < N_PTS; i++)
			new_height(i);
}


/// OVERRIDES

void TunnelFG::draw()
{
  draw::height_fill(above, N_PTS, SEGMENT_L, V2f(offset_x, 0.0f),
                    head_i, COLOUR_FILL);
  draw::height_line(above, N_PTS, SEGMENT_L, V2f(offset_x, 0.0f),
                    head_i, COLOUR_LINE);

  draw::height_fill(below, N_PTS, SEGMENT_L, V2f(offset_x, global::viewport.h),
                    head_i, COLOUR_FILL);
  draw::height_line(below, N_PTS, SEGMENT_L, V2f(offset_x, global::viewport.h),
                    head_i, COLOUR_LINE);
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
  lower = MAX(MIN_H + girth/2, middle_y - delta);
  upper = MIN(MAX_H - girth/2, middle_y + delta);
  middle_y = RAND_BETWEEN(lower, upper);

  // avoid sharp changes!
  int prev_i = (i == 0) ? (N_PTS - 1) : i - 1;
  double prev_above = above[prev_i], prev_below = below[prev_i];

  // change top
  lower = MAX(MIN_H, prev_above - delta);
  upper = MIN(prev_above + delta, middle_y - girth / 2);
  above[i] = RAND_BETWEEN(lower, upper);

  // change bottom
  lower = MAX(middle_y + girth / 2, prev_below - delta);
  upper = MIN(MAX_H, prev_below + delta);
  below[i] = RAND_BETWEEN(lower, upper);
}
