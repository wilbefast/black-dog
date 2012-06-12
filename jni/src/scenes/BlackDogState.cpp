#include "BlackDogState.hpp"

#include "../gameplay/things/AngelThing.hpp"
#include "../global.hpp"                          // for viewport

/// CREATION, DESTRUCTION

BlackDogState::BlackDogState() :
GameState(),
parallax(),
obstacle()
{
  addThing(new AngelThing(V2i(WINDOW_DEFAULT_W/4, WINDOW_DEFAULT_H/2)));
}

/// OVERRIDES GAMESTATE

int BlackDogState::update()
{
  int result;

  // Update dynamic game objects
  result = GameState::update();
  if(result != CONTINUE)
    return result;

  // Update background parallax tunnel
  parallax.update();

  // Update forground obstacle tunnel
  obstacle.update();

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
}

/// QUERY

const TunnelFG* BlackDogState::getObstacle() const
{
  return &obstacle;
}
