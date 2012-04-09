#include "BlackDogState.hpp"

#include "../gameplay/things/AngelThing.hpp"
#include "../global.hpp"                          // for viewport

/// CREATION, DESTRUCTION

BlackDogState::BlackDogState() :
GameState(),
parallax(),
obstacle()
{
  addThing(new AngelThing(V2i(global::viewport.w/4, global::viewport.h/2)));
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
  // Draw the background parallax tunnel
  parallax.draw();

  // Draw the foreground obstacle tunnel
  obstacle.draw();

  // Draw dynamic game objects
  GameState::draw();
}
