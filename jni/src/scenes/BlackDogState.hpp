#ifndef BLACKDOGSTATE_HPP_INCLUDED
#define BLACKDOGSTATE_HPP_INCLUDED

#include "GameState.hpp"

class BlackDogState : public GameState
{
  /// CONSTANTS
private:

  /// ATTRIBUTES
private:
  TunnelBG parallax;
  TunnelFG obstacle;

  /// METHODS
public:
  // Creation, destruction
  BlackDogState();
  // Overrides GameState
  int update();
  void draw();
};

#endif // BLACKDOGSTATE_HPP_INCLUDED
