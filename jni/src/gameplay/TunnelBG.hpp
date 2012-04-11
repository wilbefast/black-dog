#ifndef TUNNELBG_INCLUDED
#define TUNNELBG_INCLUDED

#include "Tunnel.hpp"
#include "../graphics/draw.hpp"

// background tunnel: purely decorative.

class TunnelBG : public Tunnel
{
  /// CONSTANTS
private:
  static draw::Colour COLOUR_FILL;
  static const int DEFAULT_SPEED = 1;
  /// METHODS
public:
  TunnelBG();
  /// OVERRIDES
public:
  void draw();
private:
  void new_height(unsigned int i);
};

#endif // TUNNELBG_INCLUDED
