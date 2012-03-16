#ifndef TUNNELBG_INCLUDED
#define TUNNELBG_INCLUDED

#include "Tunnel.hpp"

// background tunnel: purely decorative.

class TunnelBG : public Tunnel
{
  /// CONSTANTS
private:
  static const int DEFAULT_SPEED = 1;
  /// METHODS
public:
  TunnelBG();
  /// OVERRIDES
private:
  void new_height(unsigned int i);
};

#endif // TUNNELBG_INCLUDED
