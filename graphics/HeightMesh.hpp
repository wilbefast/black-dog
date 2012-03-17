#ifndef HEIGHTMESH_HPP_INCLUDED
#define HEIGHTMESH_HPP_INCLUDED

#include "Mesh2D.hpp"

class HeightMesh : public Mesh2D
{
  /// ATTRIBUTES
private:
  unsigned int n_segments;
  float spacing_x, base_y;
  /// METHODS
public:
  // construction, destruction
  HeightMesh(unsigned int _n_segments, float _spacing_x, float _base_y);
  void bake(float height[]);
  void add(float new_height);
private:
  // subroutines
  void triangulateSegment(V2f& lower, V2f& higher, int &v_i);
};

#endif // HEIGHTMESH_HPP_INCLUDED
