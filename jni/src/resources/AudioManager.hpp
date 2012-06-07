#ifndef AUDIOMANAGER_HPP_INCLUDED
#define AUDIOMANAGER_HPP_INCLUDED

#include "SDL.h"                // must be included before SDL_mixer !
#include "SDL_mixer.h"          // Mix_Music

#include <map>
#include "numerise.hpp"         // for str_id

typedef std::map<str_id, Mix_Chunk*> SoundMap;
typedef SoundMap::iterator SoundI;

class AudioManager
{
  /// CONSTANTS
private:
  static const int DEFAULT_FREQUENCY = 22050;     // 48000 ? 44100 ? 22050 ?
  static const int DEFAULT_CHUNK_SIZE = 4096;     // 1024 ?

  /// SINGLETON
private:
  static AudioManager* instance;
public:
  static AudioManager* getInstance();

  /// ATTRIBUTES
private:
  bool started;
  // music
  Mix_Music* music;
  SDL_RWops* music_file;
  #ifdef __ANDROID__
    const char* sdcard_file;
  #endif // #ifdef __ANDROID__
  // sound
  SoundMap sounds;

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
  void stop_music();
  void unload_music();
  // sound
  int load_sound(const char* source_file, const char* name);
  int play_sound(const char* name);
};

#endif // AUDIOMANAGER_HPP_INCLUDED
