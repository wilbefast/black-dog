#include "TunnelBG.hpp"

#include "../global.hpp"
#include "../wjd_math.hpp"


/// CONSTRUCTION AND DESTRUCTION

TunnelBG::TunnelBG() :
Tunnel(DEFAULT_SPEED)
{
    // randomise initial values
		for (int i = 0; i < N_PTS; i++)
			new_height(i);
}

/// OVERRIDES

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
