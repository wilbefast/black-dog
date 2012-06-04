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
  /// 1. Load textures
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("menus.png"), "menus")
      == EXIT_SUCCESS, "Loading menu graphics texture");
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("sprites.png"), "sprites")
      == EXIT_SUCCESS, "Loading gameplay sprite-sheet texture");


  /// 2. Create animations
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
                                            iRect(0, 1, 64, 64), 4, "wraith")
      == EXIT_SUCCESS, "Creating 'wraith' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
                                            iRect(0, 64, 64, 64), 4, "weights")
      == EXIT_SUCCESS, "Creating 'weights' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
                                      iRect(0, 128, 64, 64), 4, "angel")
      == EXIT_SUCCESS, "Creating 'angel' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
                                    iRect(256, 128, 64, 64), 4, "cloak")
    == EXIT_SUCCESS, "Creating 'angel' animation");


  /// 3. Load and play the music track
  ASSERT(AudioManager::getInstance()->load_music(GET_ASSET("music.ogg"))
        == EXIT_SUCCESS, "Loading initial music track");
  ASSERT(AudioManager::getInstance()->play_music(true)
        == EXIT_SUCCESS, "Setting initial music track to loop");


  /// 4. Load sound files
  /*
  ASSERT(AudioManager::getInstance()->
    load_sound(GET_ASSET("chain_snap.wav"), "chain_snap") == EXIT_SUCCESS,
    "Loading 'chain_snap' sound");
  */


  /// 5. No problems, return success code!
  return EXIT_SUCCESS;
}
