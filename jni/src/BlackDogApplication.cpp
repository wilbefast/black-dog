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
#include "BlackDogApplication.hpp"

#include "resources/GraphicsManager.hpp"
#include "resources/AudioManager.hpp"
#include "resources/file.hpp"             // for GET_ASSET

#include "assert.hpp"                     // for ASSERT

#include "scenes/MainMenu.hpp"             // initial scene

/// CONSTRUCTION & DESTRUCTION

BlackDogApplication::BlackDogApplication() :
Application(new MainMenu())
{
}

/// OVERRIDES

int BlackDogApplication::loadResources()
{
  /*/// 3. Load and play the music track
  ASSERT(AudioManager::getInstance()->load_music(GET_ASSET("music.ogg"))
        == EXIT_SUCCESS, "Loading initial music track");
  ASSERT(AudioManager::getInstance()->play_music(true)
        == EXIT_SUCCESS, "Setting initial music track to loop");*/

  /// 5. No problems, return success code!
  return EXIT_SUCCESS;
}
