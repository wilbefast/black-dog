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
  static const int DEFAULT_MIN_GIRTH = 96;
  static const int DEFAULT_SPEED = 4;

	/// ATTRIBUTES
private:
	// 'pseudo-constants' as these will be set based on window size
	// girth is the vertical size of the tunnel
	const float MIN_GIRTH;
	const float BASE_GIRTH;
	// maximum vertical change between two points
	const float MAX_DELTA;
	// height of the middle of the tunnel
  float middle_y;
	// the current difficulty in [0, 1]
  float difficulty;

  /// METHODS
public:
  TunnelFG();

	/// OVERRIDES
public:
  void draw();
private:
  void new_height(unsigned int i);
};

#endif // TUNNELFG_HPP_INCLUDED
