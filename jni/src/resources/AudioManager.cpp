#include "AudioManager.hpp"

#include "../assert.hpp"
#include "../warn.hpp"
#include "../math/wjd_math.hpp"
#include "file.hpp" // for io::MAX_BLOCKS

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
started(false),
music(NULL),
music_file(NULL),
sounds()
{
}

int AudioManager::startup()
{
  if(started)
    WARN_RTN("AudioManager::startup","already started!", EXIT_SUCCESS);

  //Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  ASSERT_MIX(Mix_OpenAudio(DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
           MIX_DEFAULT_CHANNELS, DEFAULT_CHUNK_SIZE) != -1,
          "Starting SDL Mixer");

  // All good!
  started = true;
  return EXIT_SUCCESS;
}

int AudioManager::shutdown()
{
  if(!started)
    WARN_RTN("AudioManager::shutdown","already shutdown!", EXIT_SUCCESS);

  // Clean up the sound
  for(SoundI i = sounds.begin(); i != sounds.end(); i++)
    Mix_FreeChunk((*i).second);

  // Clean up the music
  unload_music();

  // Shut down audio -- this may take a few seconds
  LOG_I("SDL Mixer shutdown", "Pending...");
  Mix_CloseAudio();
  LOG_I("SDL Mixer shutdown", "Okay");

  // All good!
  started = false;
  return EXIT_SUCCESS;
}


AudioManager::~AudioManager()
{
  if(started)
    shutdown();
}

/// MUSIC

int AudioManager::load_music(const char* source_file)
{
  // Attempt to open the music file
  music_file = SDL_RWFromFile(source_file, "rb"); // read binary
  ASSERT(music_file, source_file); // print the name of the file being opened

  #ifdef __ANDROID__

    // we'll externalise the music file to the SD card ...
    /*SDL_RWops* out = SDL_RWFromFile("/sdcard/data/music.ogg", "wb");
    ASSERT(out, "Opening file to export music from APK to filesystem");

    char buffer[io::MAX_BLOCKS];
    int read_amount = SDL_RWread(music_file, buffer, 1, io::MAX_BLOCKS);
    while(read_amount > 0)
    {
      SDL_RWwrite(out, buffer, 1, read_amount);
      SDL_RWseek(music_file, SEEK_CUR, read_amount*io::BLOCK_SIZE);
      read_amount = SDL_RWread(music_file, buffer, 1, io::MAX_BLOCKS);
    }
    SDL_RWclose(out);*/
    SDL_RWclose(music_file);

    /*FILE* file;
    file = fopen("/sdcard/data/bink.txt", "rb");
    ASSERT(file, "opening file");


    char buffer[30];
    int read_amount = fread(buffer, 8, 30, file);


    char bb[20];
    sprintf(bb, "read %d", read_amount);
    LOG_I(bb, buffer);

    fclose(file);*/

    SDL_RWops *rw;
    rw = SDL_RWFromFile("/sdcard/data/music.ogg", "rb");
    ASSERT(rw, "testing testing 1, 2, 3");
    SDL_RWclose(rw);


    ASSERT_MIX(music = Mix_LoadMUS("/sdcard/data/music.ogg"),
            "Loading music from filesystem");

  #else // desktop platforms

    // Attempt to read the file contents as music
    ASSERT_MIX(music = Mix_LoadMUS_RW(music_file),
                "Extracting music from SDL_RWops structure");

  #endif //ifdef __ANDROID__

  /// NB - file is NOT closed as music data must be streamed



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
    /// FIXME
    music_file = NULL;
  }
}


/// SOUND

int AudioManager::load_sound(const char* source_file, const char* name)
{
  // load wave file
  Mix_Chunk* new_sound = Mix_LoadWAV(source_file);
  // check that the sound was loaded successfully
  ASSERT_MIX(new_sound, source_file);
  // save under requested name
  str_id hash = numerise(name);
  sounds[hash] = new_sound;

  // All clear !
  return EXIT_SUCCESS;
}

int AudioManager::play_sound(const char* name)
{
  // search for the resource
  str_id hash = numerise(name);
  SoundI i = sounds.find(hash);
  // make sure that it is found
  if(i == sounds.end())
    WARN_RTN("AudioManager::play_sound invalid identifier", name, EXIT_FAILURE);
  // attempt to play the sound if it is
  if(Mix_PlayChannel(-1, (*i).second, 0) == -1)
    WARN_RTN("AudioManager::play_sound", Mix_GetError(), EXIT_FAILURE);

  // All clear !
  return EXIT_SUCCESS;
}
