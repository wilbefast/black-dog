#ifndef TUNNEL_HPP_INCLUDED
#define TUNNEL_HPP_INCLUDED

#include "../V2.hpp"

class Tunnel
{
	/// CONSTANTS
protected:
  static const int DEFAULT_MIN_H = 24;
  static const int N_PTS = 12;

	/// ATTRIBUTES
protected:
	// 'pseudo-constants' as these will be set based on window size
  const float MIN_H;
	const float MAX_H;
  // the segment length is the distance between two points
	const float SEGMENT_L;
	// index of start of height maps
	unsigned int head_i;
	// height maps themselves (circular buffers)
	float above[N_PTS];
  float below[N_PTS];

	// horizontal offset of the tunnel (for smooth looping of buffers)
  float offset_x;
  float speed_x;

	/** METHODS **/
public:
	// creation
  Tunnel(float base_speed);
	// loop
  void update();
  void draw();
	// query
  bool collision(V2f& position);


	/** SUB-ROUTINES **/
protected:
	virtual void new_height(unsigned int i);
	float index_to_x(unsigned int i);
	float x_to_height(float x, float hmap[]);
  void build_drawable(float h_map[], float base_y, V2f result[]);
};

#endif // TUNNEL_HPP_INCLUDED
