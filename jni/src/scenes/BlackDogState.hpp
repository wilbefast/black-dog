#ifndef BLACKDOGSTATE_HPP_INCLUDED
#define BLACKDOGSTATE_HPP_INCLUDED

#include "GameState.hpp"

#include "../gameplay/TunnelBG.hpp"
#include "../gameplay/TunnelFG.hpp"

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
  // query
  const TunnelFG* getObstacle() const;

  /// SUBROUTINES
private:
  void draw_feather_ui();
  void draw_progress_ui();
};

#endif // BLACKDOGSTATE_HPP_INCLUDED
