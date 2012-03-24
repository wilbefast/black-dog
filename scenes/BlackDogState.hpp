#ifndef BLACKDOGSTATE_HPP_INCLUDED
#define BLACKDOGSTATE_HPP_INCLUDED

#include "GameState.hpp"

class BlackDogState : public GameState
{
private:
  TunnelBG parallax;
  TunnelFG obstacle;

public:
  // Creation, destruction
  BlackDogState();
  // Overrides GameState
  int update();
  void draw();
};

#endif // BLACKDOGSTATE_HPP_INCLUDED
