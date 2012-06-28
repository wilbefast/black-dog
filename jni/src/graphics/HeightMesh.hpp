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
#ifndef HEIGHTMESH_HPP_INCLUDED
#define HEIGHTMESH_HPP_INCLUDED

#include "Mesh2D.hpp"

class HeightMesh : public Mesh2D
{
  /// ATTRIBUTES
private:
  unsigned int n_segments;
  float spacing_x, base_y;
  bool roof;
  /// METHODS
public:
  // construction, destruction
  HeightMesh(unsigned int _n_segments, float _spacing_x, float _base_y);
  void bake(float height[]);
  void add(float new_height);
private:
  // subroutines
  void triangulateSegment(const V2f& lower, const V2f& higher, int &v_i);
  void sortHeight(const V2f& a, const V2f& b, V2f& lower, V2f& higher);
};

#endif // HEIGHTMESH_HPP_INCLUDED
