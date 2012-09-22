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
#ifndef FONTMANAGER_HPP_INCLUDED
#define FONTMANAGER_HPP_INCLUDED

#include "SDL.h"
#include "SDL_ttf.h"

#include <map>
#include "../math/numerise.hpp"         // for str_id

#include "ResourceManager.hpp"

// custom assert
#include "../assert.hpp"
#define ASSERT_TTF(assertion, what)                     \
    ASSERT_AUX(assertion, what, TTF_GetError())

//typedef std::map<str_id, Mix_Chunk*> SoundMap;
//typedef SoundMap::iterator SoundI;

class FontManager : public ResourceManager
{
  /// CONSTANTS

  /// SINGLETON
private:
  static FontManager* instance;
public:
  static FontManager* getInstance();

  /// ATTRIBUTES
private:

  /// METHODS
private:
  // creation & destruction
  FontManager();
public:
  ~FontManager();
  // loading -- overrides ResourceManager
  int load();
  int unload();
  int parse_root(void* root_handle);
  int parse_element(void* element);
};

#endif // FONTMANAGER_HPP_INCLUDED
