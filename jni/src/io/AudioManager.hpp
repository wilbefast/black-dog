/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef AUDIOMANAGER_HPP_INCLUDED
#define AUDIOMANAGER_HPP_INCLUDED

#include "SDL.h"                // must be included before SDL_mixer !
#include "SDL_mixer.h"          // Mix_Music

#include <map>
#include "../math/numerise.hpp"         // for str_id

#include "ResourceManager.hpp"

// custom assertion
#include "../assert.hpp"
#define ASSERT_MIX(assertion, what)                     \
    ASSERT_AUX(assertion, what, Mix_GetError())

#define SOUND_FILETYPE "wav"
#define MUSIC_FILETYPE "ogg"
#define VOLUME_STEP MIX_MAX_VOLUME/14

typedef std::map<str_id, Mix_Chunk*> SoundMap;
typedef SoundMap::iterator SoundI;

class AudioManager : public ResourceManager
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
  unsigned short volume; // value between 0 and MIX_MAX_VOLUME = 128
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
  ~AudioManager();
  // loading -- overrides ResourceManager
  int load();
  int unload();
  int parse_root(void* root_handle);
  int parse_element(void* element);
  // global volume
  void volume_up();
  void volume_down();
  // music
  int load_music(const char* source_file);
  int play_music(bool loop);
  void stop_music();
  void unload_music();
  // sound
  int load_sound(const char* source_file, const char* name);
  int play_sound(const char* name);
  int play_sound(str_id id);
private:
  void set_volume(unsigned short new_volume);
};

#endif // AUDIOMANAGER_HPP_INCLUDED
