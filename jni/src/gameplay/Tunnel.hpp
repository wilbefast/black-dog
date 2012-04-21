#ifndef TUNNEL_HPP_INCLUDED
#define TUNNEL_HPP_INCLUDED

#include "../global.hpp"              // for WINDOW_DEFAULT_H
#include "../math/V2.hpp"
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
	static const float SEGMENT_L;

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
  void update();
  virtual void draw();
	// query
  bool collision(V2f& position);


	/** SUB-ROUTINES **/
protected:
	virtual void new_height(unsigned int i);
	float index_to_x(unsigned int i);
	float x_to_height(float x, float hmap[]);
};

#endif // TUNNEL_HPP_INCLUDED
