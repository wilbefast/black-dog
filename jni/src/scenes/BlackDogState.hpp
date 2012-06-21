#ifndef BLACKDOGSTATE_HPP_INCLUDED
#define BLACKDOGSTATE_HPP_INCLUDED

#include "GameState.hpp"

#include "../gameplay/TunnelBG.hpp"
#include "../gameplay/TunnelFG.hpp"

class BlackDogState : public GameState
{
  /// CONSTANTS
private:
  static const int STARTING_PROGRESS = WINDOW_DEFAULT_W * 0.15f;
  static const int PROGRESS_THRESHOLD = WINDOW_DEFAULT_W * 0.25f;
  static const float PROGRESS_MAX = WINDOW_DEFAULT_W * 0.8f;
  static const float BASE_DIFFICULTY = 0.2f;

  /// ATTRIBUTES
private:
  TunnelBG parallax;
  TunnelFG obstacle;
  float player_progress;

  /// METHODS
public:
  // Creation, destruction
  BlackDogState();
  // Overrides GameState
  int update(float delta);
  void draw();
  // query
  const TunnelFG* getObstacle() const;
  // modification
  void setDifficulty(float _difficulty);

  /// SUBROUTINES
private:
  void draw_feather_ui();
  void draw_progress_ui();
};

#endif // BLACKDOGSTATE_HPP_INCLUDED
