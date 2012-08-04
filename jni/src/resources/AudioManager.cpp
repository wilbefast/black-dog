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

  // load audio
  ASSERT(load_xml(GET_ASSET("audio.xml")) == EXIT_SUCCESS,
        "Loading audio assets based on 'audio.xml'");

  // All good!
  started = true;
  return EXIT_SUCCESS;
}

int AudioManager::load_xml(const char* xml_file)
{
  // pass string to the TinyXML document
  TiXmlDocument doc;
  ASSERT_AUX(io::read_xml(xml_file, &doc) == EXIT_SUCCESS,
            "Opening audio pack XML file", doc.ErrorDesc());

  // create local variables for searching document tree
  TiXmlHandle doc_handle(&doc);
  TiXmlElement* element = NULL;

  // the root is a 'audio' tag
  element = doc_handle.FirstChildElement("audio").Element();
  TiXmlHandle root_handle = TiXmlHandle(element);

  // load music
  element = root_handle.FirstChild("music").Element();
  const char* name = element->Attribute("name");
  if(!name)
    WARN_RTN("AudioManager::load_xml", "malformed music tag", EXIT_FAILURE);
  string filename = io::name_to_path(name, MUSIC_FILETYPE);
  ASSERT(load_music(filename.c_str()) == EXIT_SUCCESS, "Loading initial music track");
  ASSERT(play_music(true) == EXIT_SUCCESS, "Setting initial music track to loop");

  // load sound effects
  element = root_handle.FirstChild("sound_list").FirstChild().Element();
  while(element)
  {
    // get the name of the texture and deduce its filename
    name = element->Attribute("name");
    if(!name)
      WARN_RTN("AudioManager::load_xml", "malformed sound tag", EXIT_FAILURE);

    // load the texture
    string filename = io::name_to_path(name, SOUND_FILETYPE);
    load_sound(filename.c_str(), name);

    // continue to the next sprite
    element = element->NextSiblingElement();
  }

  // all good
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
  // hash the string to find the resource
  if(play_sound(numerise(name)) == EXIT_FAILURE)
    WARN_RTN("AudioManager::play_sound invalid identifier", name, EXIT_FAILURE);

  return EXIT_SUCCESS;
}

int AudioManager::play_sound(str_id id)
{
  // search for the resource
  SoundI i = sounds.find(id);
  // make sure that it is found
  if(i == sounds.end())
    return EXIT_FAILURE;
  // attempt to play the sound if it is
  if(Mix_PlayChannel(-1, (*i).second, 0) == -1)
    WARN_RTN("AudioManager::play_sound", Mix_GetError(), EXIT_FAILURE);

  // All clear !
  return EXIT_SUCCESS;
}
