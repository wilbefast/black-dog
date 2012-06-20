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
  /*
    NB - newer versions of Arrogance Engine features automatic resources loading
    based on XML descriptor files.
  */


  /// 1. Load textures
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("menus.png"), "menus")
      == EXIT_SUCCESS, "Loading menu graphics texture");
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("wraith.png"), "wraith")
      == EXIT_SUCCESS, "Loading gameplay sprite-sheet texture");
  ASSERT(GraphicsManager::getInstance()->load_texture(GET_ASSET("dog.png"), "dog")
    == EXIT_SUCCESS, "Loading gameplay sprite-sheet texture");


  /// 2. Create animations
  ASSERT(GraphicsManager::getInstance()->create_animation("wraith",
        iRect(1, 0, 96, 64), 6, "wraith_flap") == EXIT_SUCCESS,
        "Creating wraith_flap animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("wraith",
        iRect(289, 64, 96, 64), 3, "wraith_fall") == EXIT_SUCCESS,
        "Creating 'wraith_fall' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("wraith",
        iRect(1, 64, 96, 64), 3, "wraith_glide") == EXIT_SUCCESS,
        "Creating 'wraith_glide' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("wraith",
      iRect(577, 64, 96, 64), 3, "wraith_stun") == EXIT_SUCCESS,
      "Creating 'wraith_stun' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("wraith",
      iRect(928, 0, 32, 32), 2, "feather_ui") == EXIT_SUCCESS,
      "Creating 'feather_ui' animation");

  ASSERT(GraphicsManager::getInstance()->create_animation("dog",
    iRect(0, 0, 70, 128), 10, "dog_spawn") == EXIT_SUCCESS,
    "Creating 'dog_spawn' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("dog",
    iRect(0, 128, 70, 128), 5, "dog_idle") == EXIT_SUCCESS,
    "Creating 'dog_idle' animation");
  ASSERT(GraphicsManager::getInstance()->create_animation("dog",
    iRect(350, 128, 70, 128), 1, "dog_bite") == EXIT_SUCCESS,
    "Creating 'dob_bite' animation");


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

  ASSERT(AudioManager::getInstance()->
  load_sound(GET_ASSET("slime.wav"), "slime") == EXIT_SUCCESS,
  "Loading 'slime' sound");


  /// 5. No problems, return success code!
  return EXIT_SUCCESS;
}
