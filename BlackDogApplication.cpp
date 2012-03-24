#include "BlackDogApplication.hpp"

#include "resources/GraphicsManager.hpp"
#include "resources/AudioManager.hpp"
#include "resources/file.hpp"             // for GET_ASSET

#include "assert.hpp"                     // for ASSERT

#include "scenes/MainMenu.hpp"             // initial scene

/// CONSTRUCTION & DESTRUCTION

BlackDogApplication::BlackDogApplication() :
Application(new MainMenu())
{
}

/// OVERRIDES

int BlackDogApplication::loadResources()
{
  // Start the graphics (textures and animations) manager
  ASSERT(GraphicsManager::getInstance()->startup()
        == EXIT_SUCCESS, "Starting Graphics Manager");
  // Load graphic resources
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("menus.png"), "menus")
      == EXIT_SUCCESS, "Loading menu graphics texture");
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("sprites.png"), "sprites")
      == EXIT_SUCCESS, "Loading gameplay sprite-sheet texture");

  // Load and play the music track
  ASSERT(AudioManager::getInstance()->load_music(GET_ASSET("music.ogg"))
        == EXIT_SUCCESS, "Loading initial music track");
  ASSERT(AudioManager::getInstance()->play_music(true)
        == EXIT_SUCCESS, "Setting initial music track to loop");

  // No problems, return success code!
  return EXIT_SUCCESS;
}
