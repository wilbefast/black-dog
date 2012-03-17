#ifndef AUDIOMANAGER_HPP_INCLUDED
#define AUDIOMANAGER_HPP_INCLUDED

#include "SDL.h"                // must be included before SDL_mixer !
#include "SDL_mixer.h"          // Mix_Music

#define SOUND_DEFAULT_FREQUENCY 44100   // 48000 ?
#define SOUND_DEFAULT_CHUNK_SIZE 2400   // 1024 ?

class AudioManager
{
  /// SINGLETON
private:
  static AudioManager* instance;
public:
  static AudioManager* getInstance();

  /// ATTRIBUTES
private:
  // music
  Mix_Music* music;
  SDL_RWops* music_file;

  /// METHODS
private:
  // creation & destruction
  AudioManager();
public:
  int startup();
  int shutdown();
  ~AudioManager();
  // music
  int load_music(const char* source_file);
  int play_music(bool loop);
  void unload_music();
};

#endif // AUDIOMANAGER_HPP_INCLUDED
