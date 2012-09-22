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

#include "ResourceManager.hpp"

#include <map>
#include "../math/numerise.hpp"         // for str_id
#include "../graphics/draw.hpp"         // for draw::Colour

// custom assert
#include "../assert.hpp"
#define ASSERT_TTF(assertion, what)                     \
    ASSERT_AUX(assertion, what, TTF_GetError())

#define FONT_FILETYPE "ttf"

typedef std::map<str_id, TTF_Font*> TTFMap;
typedef TTFMap::iterator TTFI;

class FontManager : public ResourceManager
{
  /// NESTING
  enum text_quality_t
  {
    SOLID,  /* no anti-aliasing = fast */
    SHADED, /* anti-aliased onto a background = fast */
    BLENDED /* anti-aliased = slow */
  };

  /// CONSTANTS

  /// SINGLETON
private:
  static FontManager* instance;
public:
  static FontManager* getInstance();

  /// ATTRIBUTES
private:
  TTFMap ttf;

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
  // true-type fonts (TTFs)
  int load_ttf(const char* source_file, const char* name, unsigned int pt_size);
  // draw text
  SDL_Surface* text_surface(const char* text, const char* font_name,
                              draw::Colour f_colour = draw::Colour(0, 0, 0),
                              draw::Colour bg_colour = draw::Colour(255, 255, 255),
                              text_quality_t quality = BLENDED);
  // utilties
private:
  TTF_Font* get_ttf(str_id name);
  TTF_Font* get_ttf(const char* name);

};

#endif // FONTMANAGER_HPP_INCLUDED
