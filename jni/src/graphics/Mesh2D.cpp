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
