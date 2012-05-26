#include "BlackDogState.hpp"


#include "../resources/AudioManager.hpp" // testing sound (remove this)

#include "../gameplay/things/AngelThing.hpp"
#include "../global.hpp"                          // for viewport

/// CREATION, DESTRUCTION

BlackDogState::BlackDogState() :
GameState(),
parallax(),
obstacle()
{
  addThing(new AngelThing(V2i(WINDOW_DEFAULT_W/4, WINDOW_DEFAULT_W/2)));
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

  /** TEST SOUND **/
  if(input.clicking && !input.clicking_previous)
    AudioManager::getInstance()->play_sound("chain_snap");

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
