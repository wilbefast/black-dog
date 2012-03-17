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
