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
ResourceManager()
{
}

FontManager::~FontManager()
{
}

/// LOADING

int FontManager::load()
{
  ASSERT_TTF(TTF_Init() != -1, "Initialising SDL_TTF (true-type font)");

  return EXIT_SUCCESS;
}

int FontManager::unload()
{
  return EXIT_SUCCESS;
}

int FontManager::parse_root(void* root_handle)
{
  // all clear!
  return EXIT_SUCCESS;
}

int FontManager::parse_element(void* element)
{
  // all clear!
  return EXIT_SUCCESS;
}
