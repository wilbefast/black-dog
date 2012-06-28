/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
