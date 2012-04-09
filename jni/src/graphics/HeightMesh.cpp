#include "HeightMesh.hpp"

#include "../warn.hpp"

/// CONSTRUCTION, DESTRUCTION

HeightMesh::HeightMesh(unsigned int _n_segments, float _spacing_x, float _base_y):
Mesh2D(3*(_n_segments-1)),
n_segments(_n_segments),
spacing_x(_spacing_x),
base_y(_base_y),
roof(true)        // we'll know after the first bake
{
  // we'll need 1 quad and 1 triangle per point (except the last point)
  // in total that's 3 triangles, 18 vertices per point (except the last point)
}

void HeightMesh::bake(float height[])
{
  // are we drawing the roof or the floor?
  WARN_IF(base_y == height[0], "HeightMesh::bake",
                              "height map value equal to base height!");
  roof = (base_y < height[0]);

  // "vertex index" keeps track of position in vertices array
  int v_i = 0;
  // x keeps track of the horizontal position
  float x = 0.0f;
  // "index" keeps track of the position in the height-map (circular array)
  for(unsigned int i = 1; i != 0; i = (i+1)%n_segments)
  {
    /// COMPARE THE TWO EXTREMITIES OF THE SEGMENT
    // we triangulate the segment between the current index and the next one
    unsigned int next_i = (i+1)%n_segments;
    V2f current(x, height[i]), next(x + spacing_x, height[next_i]);
    // we'll access these two points by height rather than index
    V2f higher, lower;
    sortHeight(current, next, lower, higher);

    /// PERFORM THE TRIANGULATION OF THE SEGMENT BASED ON THIS PRETREATMENT
    triangulateSegment(lower, higher, v_i);

    /// REMEMBER TO MOVE X FORWARD
    x += spacing_x;
  }
}

void HeightMesh::add(float new_height)
{
  // over-write the leftmost segment = 3 triangles = 9 vertices = 18 coordinates
  for(unsigned int i = 18; i < n_vertices*2; i++)
  {
    // squash the oldest 3 triangles
    vertices[i-18] = vertices[i];

    // translate x coordinates (ever second value) to the left
    if(!(i%2))
      vertices[i-18] -= spacing_x;
  }

  // triangulate the new segment
  int v_i = n_vertices*2 - 18;

  /** Remember: the last 6 coordinate pairs are arrayed as follows
  (where 1 = last, 2 = second last, 3 = third last)

             2--3                       3--2
  case 1.    | /       OR     case 2.    \ |
             1                             1

  As a result the previous height is that of the last or 3rd last pair **/

  // figure out which of these two situations we are in
  V2f current, next;
  if(vertices[v_i-4] < vertices[v_i-6])
    current = V2f(vertices[v_i-6], vertices[v_i-5]); // case 1 = third last
  else
    current = V2f(vertices[v_i-2], vertices[v_i-1]); // case 2 = last

  // we finally know the x coordinate of the new vertex
  next = V2f(current.x + spacing_x, new_height);

  // we'll access these two points by height rather than index
  V2f higher, lower;
  sortHeight(current, next, lower, higher);

  /// PERFORM THE TRIANGULATION OF THE SEGMENT BASED ON THIS PRETREATMENT
  triangulateSegment(lower, higher, v_i);
}


/// SUBROUTINES

void HeightMesh::triangulateSegment(const V2f& lower, const V2f& higher,
                                    int &v_i)
{
    /** QUAD, triangle 1

            1--2               2--1
      1 ->  | /.      OR       .\ |  <- 1
            |/ .               . \|
            3...               ...3
            . .                 . .
            .                     .
    **/
    // triangle 1, point 1
    vertices[v_i++] = higher.x;           // x
    vertices[v_i++] = base_y;             // y
    // triangle 1, point 2
    vertices[v_i++] = lower.x;            // x
    vertices[v_i++] = base_y;             // y
    // triangle 1, point 3
    vertices[v_i++] = higher.x;           // x
    vertices[v_i++] = lower.y;            // y

    /** QUAD, triangle 2

            ...1               1...
      2 ->  . /|      OR       |\ .  <- 2
            ./ |               | \.
            2--3               3--2
            . .                 . .
            .                     .
    **/
    // triangle 2, point 1
    vertices[v_i++] = lower.x;            // x
    vertices[v_i++] = base_y;             // y
    // triangle 2, point 2
    vertices[v_i++] = higher.x;           // x
    vertices[v_i++] = lower.y;            // y
    // triangle 2, point 3
    vertices[v_i++] = lower.x;            // x
    vertices[v_i++] = lower.y;            // y

     /** BOTTOM, triangle 3

            ....               ....
            . ..      OR       .. .
            .. .               . ..
            2--1               1--2
      3 ->  | /                 \ |  <- 3
            3                     3
    **/
    // triangle 3, point 1
    vertices[v_i++] = lower.x;            // x
    vertices[v_i++] = lower.y;            // y
    // triangle 3, point 2
    vertices[v_i++] = higher.x;           // x
    vertices[v_i++] = lower.y;            // y
    // triangle 3, point 3
    vertices[v_i++] = higher.x;           // x
    vertices[v_i++] = higher.y;           // y
}

void HeightMesh::sortHeight(const V2f& start, const V2f& end, V2f& lower,
                            V2f& higher)
{
    bool descending = (start.y < end.y);  // remember: y = 0 at the *top*
    if((roof && descending) || (!roof && !descending))
    {
      higher = end;
      lower = start;
    }
    else
    {
      higher = start;
      lower = end;
    }
}
