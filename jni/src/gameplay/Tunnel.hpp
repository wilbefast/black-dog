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
#ifndef TUNNEL_HPP_INCLUDED
#define TUNNEL_HPP_INCLUDED

#include "../global.hpp"              // for WINDOW_DEFAULT_H
#include "../math/V2.hpp"
#include "../math/Rect.hpp"
#include "../graphics/HeightMesh.hpp"

class Tunnel
{
	/// CONSTANTS
protected:
  static const int N_PTS = 12;
	static const int BASE_ABOVE = 0;
	static const int BASE_BELOW = WINDOW_DEFAULT_H;
  static const int MIN_H = 24;
	static const int MAX_H = WINDOW_DEFAULT_H - MIN_H;
  // the segment length is the distance between two points
	static const int SEGMENT_L = WINDOW_DEFAULT_W / (N_PTS-2);

  /// ATTRIBUTES
	// index of start of height maps
	unsigned int head_i;
	// height maps themselves (circular buffers)
	float above[N_PTS];
  float below[N_PTS];
	// horizontal offset of the tunnel (for smooth looping of buffers)
  float offset_x;
  float speed_x;
  // cache for drawing meshes
  HeightMesh mesh_above, mesh_below;

	/** METHODS **/
public:
	// creation
  Tunnel(float _speed_x);
	// loop
  void update(float delta);
  virtual void draw();
	// query
  V2i collidingPoint(V2f position) const;
  V2i collidingRect(fRect hitbox) const;


	/** SUB-ROUTINES **/
protected:
	virtual void new_height(unsigned int i);
	float index_to_x(unsigned int i) const;
	int x_to_index(float x, const float hmap[]) const;
	float x_to_height(float x, const float hmap[]) const;
	float x_to_slope(float x, const float hmap[]) const;
	float y_to_seg_x(float y, const float hmap[], unsigned int i) const;
};

#endif // TUNNEL_HPP_INCLUDED
