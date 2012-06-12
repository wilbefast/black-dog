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
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("sheet.png"), "sprites")
      == EXIT_SUCCESS, "Loading gameplay sprite-sheet texture");


  /// 2. Create animations
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
        iRect(0, 1, 96, 64), 6, "wraith_flap") == EXIT_SUCCESS,
        "Creating wraith_flap animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
        iRect(288, 65, 96, 64), 3, "wraith_fall") == EXIT_SUCCESS,
        "Creating 'wraith_fall' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
        iRect(0, 65, 96, 64), 3, "wraith_glide") == EXIT_SUCCESS,
        "Creating 'wraith_glide' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("sprites",
      iRect(576, 65, 96, 64), 3, "wraith_stun") == EXIT_SUCCESS,
      "Creating 'wraith_stun' animation");

  /// 3. Load and play the music track
  ASSERT(AudioManager::getInstance()->load_music(GET_ASSET("music.ogg"))
        == EXIT_SUCCESS, "Loading initial music track");
  ASSERT(AudioManager::getInstance()->play_music(true)
        == EXIT_SUCCESS, "Setting initial music track to loop");


  /// 4. Load sound files
  ASSERT(AudioManager::getInstance()->
    load_sound(GET_ASSET("chain_snap.wav"), "chain_snap") == EXIT_SUCCESS,
    "Loading 'chain_snap' sound");

  ASSERT(AudioManager::getInstance()->
  load_sound(GET_ASSET("flap.wav"), "flap") == EXIT_SUCCESS,
  "Loading 'flap' sound");

  ASSERT(AudioManager::getInstance()->
  load_sound(GET_ASSET("scream.wav"), "scream") == EXIT_SUCCESS,
  "Loading 'scream' sound");

  ASSERT(AudioManager::getInstance()->
  load_sound(GET_ASSET("swallow.wav"), "swallow") == EXIT_SUCCESS,
  "Loading 'swallow' sound");


  /// 5. No problems, return success code!
  return EXIT_SUCCESS;
}
