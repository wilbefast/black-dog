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
	static const float MAX_DELTA;

	/// ATTRIBUTES
private:
	// height of the middle of the tunnel
  float middle_y[N_PTS];
	// the current difficulty in [0, 1]
  float difficulty;
  /// METHODS
public:
  TunnelFG(float start_difficulty = 0.0f);
  // query
  float x_to_middle(float x) const;
  // modification
  void setDifficulty(float _difficulty);

	/// OVERRIDES
public:
  void draw();
private:
  void new_height(unsigned int i);
};

#endif // TUNNELFG_HPP_INCLUDED
