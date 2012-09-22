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
#ifndef GRAPHICSMANAGER_HPP_INCLUDED
#define GRAPHICSMANAGER_HPP_INCLUDED

#include <map>
#include "../math/numerise.hpp"         // for str_id

#include "ResourceManager.hpp"

#include "../graphics/Texture.hpp"
#include "../graphics/Animation.hpp"

#define TEXTURE_FILETYPE "png"

typedef std::map<str_id, Texture*> TextureMap;
typedef TextureMap::iterator TextureI;
typedef std::map<str_id, Animation*> AnimationMap;
typedef AnimationMap::iterator AnimationI;

class GraphicsManager : public ResourceManager
{
    /// CONSTANTS
private:

  /// SINGLETON
private:
  static GraphicsManager* instance;
public:
  static GraphicsManager* getInstance();

  /// ATTRIBUTES
private:
  bool started;
  TextureMap textures;
  AnimationMap animations;

  /// METHODS
private:
  // creation & destruction
  GraphicsManager();
public:
  int startup();
  int shutdown();
  ~GraphicsManager();
  // loading -- overrides ResourceManager
  virtual int parse_root(void* root_handle);
  virtual int parse_element(void* element);
  // textures
  int load_texture(const char* source_file, const char* name);
  Texture* get_texture(const char* name);
  Texture* get_texture(str_id id);
  // animations
  int create_animation(const char* texture_name,
                      iRect frame, int n_frames, const char* name);
  Animation* get_animation(const char* name);
  Animation* get_animation(str_id id);
};

#endif // GRAPHICSMANAGER_HPP_INCLUDED
