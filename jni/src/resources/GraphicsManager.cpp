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
#include "GraphicsManager.hpp"

#include "../assert.hpp"
#include "../warn.hpp"

/// SINGLETON

GraphicsManager* GraphicsManager::instance = NULL;

GraphicsManager* GraphicsManager::getInstance()
{
  if(!instance)
    instance = new GraphicsManager();
  return instance;
}

/// CREATION & DESTRUCTION

GraphicsManager::GraphicsManager() :
started(false),
textures(),
animations()
{
}

int GraphicsManager::startup()
{
  if(started)
    WARN_RTN("GraphicsManager::startup","already started!", EXIT_SUCCESS);

  // All good!
  started = true;
  return EXIT_SUCCESS;
}

int GraphicsManager::shutdown()
{
  if(!started)
    WARN_RTN("GraphicsManager::shutdown","already shutdown!", EXIT_SUCCESS);

  // Clean up the animations
  for(AnimationI i = animations.begin(); i != animations.end(); i++)
    delete (*i).second;

  // Clean up the textures
  for(TextureI i = textures.begin(); i != textures.end(); i++)
  {
    if((*i).second->unload() != EXIT_SUCCESS)
      WARN_RTN("GraphicsManager::shutdown", "Failed to unload texture", EXIT_FAILURE);
    delete (*i).second;
  }

  // All good!
  started = false;
  return EXIT_SUCCESS;
}


GraphicsManager::~GraphicsManager()
{
  if(started)
    shutdown();
}


/// TEXTURES

int GraphicsManager::load_texture(const char* source_file, const char* name)
{
  // load image file
  Texture* new_texture = new Texture();
  ASSERT(new_texture->load(source_file) == EXIT_SUCCESS, source_file);

  // save under requested name
  str_id hash = numerise(name);
  textures[hash] = new_texture;

  // All clear !
  return EXIT_SUCCESS;
}

Texture* GraphicsManager::get_texture(const char* name)
{
  Texture* result = get_texture(numerise(name));
  if(!result)
    WARN("GraphicsManager::get_texture invalid identifier", name);

  return result;
}

Texture* GraphicsManager::get_texture(str_id id)
{
  // search for the resource
  TextureI i = textures.find(id);
  // make sure that it is found
  if(i == textures.end())
    return NULL;

  // return the texture we recovered
  return (*i).second;
}


/// ANIMATIONS

int GraphicsManager::create_animation(const char* texture_name,
                          iRect frame, int n_frames, const char* animation_name)
{
  // attempt to retrieve the desired texture
  Texture* animation_texture = get_texture(texture_name);
  ASSERT(animation_texture, "Looking for animation source texture");

  // create animation
  Animation* new_animation = new Animation();
  new_animation->init(animation_texture, frame, n_frames);

  // save under requested name
  str_id hash = numerise(animation_name);
  animations[hash] = new_animation;

  // All clear !
  return EXIT_SUCCESS;
}

Animation* GraphicsManager::get_animation(const char* name)
{
  Animation* result = get_animation(numerise(name));
  if(!result)
    WARN("GraphicsManager::get_animation invalid identifier", name);

  return result;
}

Animation* GraphicsManager::get_animation(str_id id)
{
  // search for the resource
  AnimationI i = animations.find(id);
  // make sure that it is found
  if(i == animations.end())
    return NULL;

  // return the animation we recovered
  return (*i).second;
}
