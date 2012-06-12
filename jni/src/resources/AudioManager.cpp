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
#ifdef __ANDROID__
  sdcard_file(NULL),
#endif // #ifdef __ANDROID__
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
    // get the name of the file and prefix it with "/sdcard/"
    /// FIXME -- why doesn't append work on Android?
    //sdcard_file = (string("/sdcard/").append(source_file)).c_str();
    sdcard_file = "/sdcard/music.ogg";

    // initialise RWops structure from file in SD card
    FILE* sdcard = fopen(sdcard_file, "wb");
    ASSERT(sdcard, "Opening file to export music from APK to filesystem");
    SDL_RWops* sdcard_rw = SDL_RWFromFP(sdcard, SDL_TRUE); // autoclose
    ASSERT(sdcard_rw, "Creating SDL_RWops structure from file pointer");

    // externalise music data from APK assets folder to the SD card
    char buffer[io::MAX_BLOCKS];
    int read_amount = SDL_RWread(music_file, buffer, 1, io::MAX_BLOCKS);
    while(read_amount > 0)
    {
      SDL_RWwrite(sdcard_rw, buffer, 1, read_amount);
      SDL_RWseek(music_file, SEEK_CUR, read_amount*io::BLOCK_SIZE);
      read_amount = SDL_RWread(music_file, buffer, 1, io::MAX_BLOCKS);
    }
    SDL_RWclose(music_file);
    SDL_RWclose(sdcard_rw);

    // load the music from the filesystem, not the archive
    sdcard = fopen(sdcard_file, "rb");
    ASSERT(sdcard, "Opening file to import music from filesystem");
    music_file = SDL_RWFromFP(sdcard, SDL_TRUE); // autoclose
    ASSERT(music_file, "Creating SDL_RWops structure from file pointer");

  #endif //ifdef __ANDROID__

  // Attempt to read the file contents as music
  ASSERT_MIX(music = Mix_LoadMUS_RW(music_file),
              "Extracting music from SDL_RWops structure");

  /// NB - file is NOT closed as music data must be streamed

  /// NB (bis) - the RWops structure 'music_file' will be freed automatically
  /// when 'music' is closed.


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

  // Close music stream
  if(music_file)
  {
    if(!music)
      // this is closed automatically by Mix_FreeMusic
      SDL_RWclose(music_file);
    music_file = NULL;
  }

  if(music)
  {
    Mix_FreeMusic(music);
    music = NULL;
  }

  #ifdef __ANDROID__
  if(sdcard_file)
  {
    remove(sdcard_file);
    //free((char*)sdcard_file);
    sdcard_file = NULL;
  }
  #endif //ifdef __ANDROID__
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
