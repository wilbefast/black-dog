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
