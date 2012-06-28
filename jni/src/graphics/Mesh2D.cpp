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
#include "Mesh2D.hpp"
#include "../global.hpp"

/// CREATION, DESTRUCTION
Mesh2D::Mesh2D(unsigned int n_triangles) :
n_vertices(n_triangles*3),
vertices(NULL)
{
  vertices = new GLfloat[n_vertices*2]; // 2 coordinates for each vertex
}

Mesh2D::~Mesh2D()
{
  delete vertices;
}

/// LOOP

void Mesh2D::draw(float offset_x, draw::Colour c)
{
  // Start up
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor4f(c.r, c.g, c.b, c.a);
  glTranslatef(offset_x*global::scale.x, 0.0f, 0.0f);
  glScalef(global::scale.x, global::scale.y, 0.0f);

  // Draw points
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  // Unfortunately there is no way we can use FAN or STRIP here or I would !
  glDrawArrays(GL_TRIANGLES, 0, n_vertices);


  // Shut down
  glColor4f(1, 1, 1, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();
}
