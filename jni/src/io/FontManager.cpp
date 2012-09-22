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

#include "FontManager.hpp"

#include "../warn.hpp"
#include "file.hpp" // for GET_ASSET

#include "tinyxml/tinyxml.h"

using namespace std;

/// SINGLETON

FontManager* FontManager::instance = NULL;

FontManager* FontManager::getInstance()
{
  if(!instance)
    instance = new FontManager();
  return instance;
}

/// CREATION & DESTRUCTION

FontManager::FontManager() :
ResourceManager(),
ttf()
{
}

FontManager::~FontManager()
{
}

/// LOADING

int FontManager::load()
{
  // start SDL_ttf
  ASSERT_TTF(TTF_Init() != -1, "Initialising SDL_TTF (true-type font)");

  // load fonts
  ASSERT(load_xml(GET_ASSET("fonts.xml")) == EXIT_SUCCESS,
        "Loading font assets based on 'fonts.xml'");

  // all clear!
  LOG_I("FontManager::load()", "Okay");
  return EXIT_SUCCESS;
}

int FontManager::unload()
{
  // Clean up the fonts
  for(TTFI i = ttf.begin(); i != ttf.end(); i++)
    TTF_CloseFont((*i).second); // returns void

  TTF_Quit(); // returns void
  // all clear!
  LOG_I("FontManager::unload()", "Okay");
  return EXIT_SUCCESS;
}

int FontManager::parse_root(void* root_handle)
{
  // cast handle to TinyXML handle
  TiXmlHandle* txml_root = (TiXmlHandle*)root_handle;

  // load true-type fonts
  ASSERT(parse_list(txml_root, "ttf_list") == EXIT_SUCCESS,
              "FontManager parsing list of true-type fonts");

  // all clear!
  return EXIT_SUCCESS;
}

int FontManager::parse_element(void* element)
{
  // cast element to TinyXML element
  TiXmlElement* txml_element = (TiXmlElement*)element;

  // font elements
  if(!strcmp(txml_element->Value(), FONT_FILETYPE))
  {
    // get the point-size
    int pt_size = -1;
    if(txml_element->QueryIntAttribute("pt_size", &pt_size) != TIXML_SUCCESS
      || pt_size < 0)
      WARN_RTN("FontManager::load_xml", "malformed ttf tag (pt_size)",
                EXIT_FAILURE);

    // get the name of the font and deduce its filename
    const char* name = txml_element->Attribute("name");
    if(!name)
      WARN_RTN("FontManager::load_xml", "malformed ttf tag (name)",
                EXIT_FAILURE);

    // at the size of the end of the name before hashing it
    char* name_and_size = new char[strlen(name) + pt_size/10 + 1];
    sprintf(name_and_size, "%s_%d", name, pt_size);

    // load the font
    string filename = io::name_to_path(name, FONT_FILETYPE);
    load_ttf(filename.c_str(), name_and_size, (unsigned int)pt_size);

    // clean up
    delete[] name_and_size;
  }

  // all clear!
  return EXIT_SUCCESS;
}

/// TRUE-TYPE FONTS

int FontManager::load_ttf(const char* source_file, const char* name,
                          unsigned int pt_size)
{
  // load ttf file
  TTF_Font* new_font = TTF_OpenFont(source_file, pt_size);
  // check that the font was loaded successfully
  ASSERT_TTF(new_font, source_file);

  // save under requested name
  str_id hash = numerise(name);
  ttf[hash] = new_font;

  // All clear !
  return EXIT_SUCCESS;
}
