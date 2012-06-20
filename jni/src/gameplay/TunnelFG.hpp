#ifndef TUNNELFG_HPP_INCLUDED
#define TUNNELFG_HPP_INCLUDED

#include "Tunnel.hpp"
#include "../graphics/draw.hpp"

// foreground tunnel: subject to difficulty, can be collided with.

class TunnelFG : public Tunnel
{

  /// CONSTANTS
private:
  static draw::Colour COLOUR_FILL, COLOUR_LINE;
  // girth is the vertical size of the tunnel
  static const int BASE_GIRTH = WINDOW_DEFAULT_H / 3;
  static const int MIN_GIRTH = 96;
  static const int DEFAULT_SPEED = 3;
	// maximum vertical change between two points
	static const float MAX_DELTA = WINDOW_DEFAULT_H / 2;

	/// ATTRIBUTES
private:
	// height of the middle of the tunnel
  float middle_y[N_PTS];
	// the current difficulty in [0, 1]
  float difficulty;
  /// METHODS
public:
  TunnelFG();
  float x_to_middle(float x);

	/// OVERRIDES
public:
  void draw();
private:
  void new_height(unsigned int i);
};

#endif // TUNNELFG_HPP_INCLUDED
