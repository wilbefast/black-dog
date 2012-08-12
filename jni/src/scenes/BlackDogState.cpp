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
#include "BlackDogState.hpp"

#include "../io/GraphicsManager.hpp"

#include "../gameplay/things/AngelThing.hpp"
#include "../gameplay/things/DogThing.hpp"
#include "../gameplay/things/PixieThing.hpp"
#include "../gameplay/things/FallingThing.hpp"
#include "../global.hpp"                          // for viewport

/// CREATION, DESTRUCTION

BlackDogState::BlackDogState() :
GameState(),
parallax(),
obstacle(BASE_DIFFICULTY),
player_progress(STARTING_PROGRESS)
{
  // add the player character
  addThing(new AngelThing(V2i(player_progress, WINDOW_DEFAULT_H/2)));
  // add the dog
  addThing(new DogThing(V2i(0, WINDOW_DEFAULT_H/2)));
  // add the progress-mesure pixie
  addThing(new PixieThing(V2i(WINDOW_DEFAULT_W/2, WINDOW_DEFAULT_H/2)));
}

/// OVERRIDES GAMESTATE

int BlackDogState::update(float delta)
{
  int result;

  // Update dynamic game objects
  result = GameState::update(delta);
  if(result != CONTINUE)
    return result;

  // Update difficulty based on player progress
  player_progress = ((AngelThing*)getHero())->getFurthestX();
  if(player_progress > PROGRESS_THRESHOLD)
    obstacle.setDifficulty(player_progress / (WINDOW_DEFAULT_W * 0.8f));

  // Update background parallax tunnel
  parallax.update(delta);

  // Update forground obstacle tunnel
  obstacle.update(delta);

  // All clear
  return EXIT_SUCCESS;
}

void BlackDogState::draw()
{
  // Draw the background colour
  draw::rectangle(global::viewport, draw::Colour(36, 6, 15));

  // Draw the background parallax tunnel
  parallax.draw();

  // Draw the foreground obstacle tunnel
  obstacle.draw();

  // Draw dynamic game objects
  GameState::draw();

  // Draw user interface
  draw_feather_ui();
  draw_orb_ui();
}

/// QUERY

float BlackDogState::getProgress() const
{
  return player_progress;
}

const TunnelFG* BlackDogState::getObstacle() const
{
  return &obstacle;
}

/// SUBROUTINES

void BlackDogState::draw_feather_ui()
{
  // constants
  static const int SIZE = 32, SPACING = -6;
  static Animation* feather_ui
    = GraphicsManager::getInstance()->get_animation("feather_ui");

  // cache
  fRect src, dest = fRect(-SPACING, -SPACING, SIZE, SIZE);
  int n_feathers = ((AngelThing*)getHero())->countFeathers();

  // iterate through each feather of total possible storage
  for(int i = 0; i < AngelThing::MAX_FEATHERS; i++, dest.x += SIZE+SPACING)
  {
    // frame 0 is a full feather, 1 is an empty one
    src = feather_ui->getFrame(i < n_feathers ? 0 : 1);
    feather_ui->getTexture()->draw(&src, &dest);
  }
}

void BlackDogState::draw_orb_ui()
{
  // constants
  static const int SIZE = 32, SPACING = 2;
  static Animation* orb_ui
    = GraphicsManager::getInstance()->get_animation("orb_ui");

  // cache
  fRect src, dest
    = fRect(WINDOW_DEFAULT_W-(SIZE+SPACING)*AngelThing::MAX_ORBS, SPACING, SIZE, SIZE);
  int n_orbs = ((AngelThing*)getHero())->countOrbs();

  // iterate through each feather of total possible storage
  for(int i = 0; i < AngelThing::MAX_ORBS; i++, dest.x += SIZE+SPACING)
  {
    // frame 0 is a full feather, 1 is an empty one
    src = orb_ui->getFrame(i < n_orbs ? 1 : 0);
    orb_ui->getTexture()->draw(&src, &dest);
  }
}
