#include "AudioManager.hpp"

#include "assert.hpp"

/// SINGLETON

AudioManager* AudioManager::instance = NULL;

AudioManager* AudioManager::getInstance()
{
  if(!instance)
    instance = new AudioManager();
  return instance;
}

/// CREATION & DESTRUCTION

AudioManager::AudioManager() :
music(NULL),
music_file(NULL)
{
}

int AudioManager::startup()
{
  //Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  ASSERT_MIX(Mix_OpenAudio(DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
           MIX_DEFAULT_CHANNELS, DEFAULT_CHUNK_SIZE) != -1,
          "Starting SDL Mixer");

  // All good!
  return EXIT_SUCCESS;
}

int AudioManager::shutdown()
{
  // Clean up the music
  unload_music();

  // Shut down audio -- this may take a few seconds
  LOG_I("SDL Mixer shutdown", "Pending...");
  Mix_CloseAudio();
  LOG_I("SDL Mixer shutdown", "Okay");

  // All good!
  return EXIT_SUCCESS;
}


AudioManager::~AudioManager()
{
  shutdown();
}

/// MUSIC

int AudioManager::load_music(const char* source_file)
{
  // Attempt to open the music file
  music_file = SDL_RWFromFile(source_file, "rb"); // read binary
  ASSERT(music_file, "Opening music file using SDL_RWops");

  // Attempt to read the file contents as music
  ASSERT_MIX(music = Mix_LoadMUS_RW(music_file),
              "Extracting music from SDL_RWops structure");
  ASSERT_MIX(Mix_PlayMusic(music, -1) != -1, "Setting music to loop");

  /// NB - file is NOT closed as music data must be stream

  // Success !
  return EXIT_SUCCESS;
}

int AudioManager::play_music(bool loop)
{
  // Check that music is indeed loaded
  ASSERT(music && music_file, "Checking that music is loaded");

  // Try to play music
  ASSERT_MIX(Mix_PlayMusic(music, (loop)?0:-1) != -1, "Setting music to loop");

  // Success !
  return EXIT_SUCCESS;
}

void AudioManager::stop_music()
{
  Mix_HaltMusic();
}

void AudioManager::unload_music()
{
  // Stop and then free music
  stop_music();
  if(music)
  {
    Mix_FreeMusic(music);
    music = NULL;
  }

  // Close music stream
  if(music_file)
  {
    //SDL_RWclose(music_file);
    music_file = NULL;
  }
}
