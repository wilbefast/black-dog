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
#ifndef MESH2D_HPP_INCLUDED
#define MESH2D_HPP_INCLUDED

#include "../platform.hpp"      // for OpenGL/GLES types
#include "draw.hpp"

class Mesh2D
{
protected:
  unsigned int n_vertices;
  GLfloat* vertices;

public:
  // creation, destruction
  Mesh2D(unsigned int n_triangles);
  virtual ~Mesh2D();
  // loop
  void draw(float offset_x, draw::Colour c = draw::Colour());
};

#endif // MESH2D_HPP_INCLUDED
