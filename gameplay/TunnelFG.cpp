#include "TunnelFG.hpp"

#include "../global.hpp"

/// CREATION AND DESTRUCTION

TunnelFG::TunnelFG() :
Tunnel(DEFAULT_SPEED),
MIN_GIRTH(global::viewport.h / WINDOW_DEFAULT_H * DEFAULT_MIN_GIRTH),
BASE_GIRTH(global::viewport.h / 3),
MAX_DELTA(global::viewport.h / 2),
middle_y(global::viewport.h / 2),
difficulty(1.0f)
{
		// randomise initial values -- must be done AFTER pseudo-constants
		for (int i = 0; i < N_PTS; i++)
			new_height(i);
}


/// OVERRIDES

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
