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

#include "file.hpp"
#include "../assert.hpp"
#include "../warn.hpp"

#include "tinyxml/tinyxml.h"

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
ResourceManager(),
textures(),
animations()
{
}

GraphicsManager::~GraphicsManager()
{
}

/// LOADING

int GraphicsManager::load()
{
  // load graphics
  ASSERT(load_xml(GET_ASSET("graphics.xml")) == EXIT_SUCCESS,
        "Loading graphical assets based on 'graphics.xml'");

  // All good!
  return EXIT_SUCCESS;
}

int GraphicsManager::unload()
{
  // Clean up the animations
  for(AnimationI i = animations.begin(); i != animations.end(); i++)
    delete (*i).second;

  // Clean up the textures
  for(TextureI i = textures.begin(); i != textures.end(); i++)
  {
    if((*i).second->unload() != EXIT_SUCCESS)
      WARN_RTN("GraphicsManager::shutdown", "Failed to unload texture",
                                            EXIT_FAILURE);
    delete (*i).second;
  }

  // All good!
  return EXIT_SUCCESS;
}

int GraphicsManager::parse_root(void* root_handle)
{
  // load textures
  ASSERT(parse_list(root_handle, "texture_list") == EXIT_SUCCESS,
              "GraphicsManager parsing list of textures");

  // load animations
  ASSERT(parse_list(root_handle, "animation_list") == EXIT_SUCCESS,
              "GraphicsManager parsing list of animations");

  // all clear!
  return EXIT_SUCCESS;
}

int GraphicsManager::parse_element(void* element)
{
  // cast element to TinyXML element
  TiXmlElement* txml_element = (TiXmlElement*)element;

  // texture element
  if(!strcmp(txml_element->Value(), "texture"))
  {
    // get the name of the texture and deduce its filename
    const char* name = txml_element->Attribute("name");
    if(!name)
      WARN_RTN("GraphicsManager::load_xml", "malformed texture tag", EXIT_FAILURE);

    // load the texture
    string filename = io::name_to_path(name, TEXTURE_FILETYPE);
    load_texture(filename.c_str(), name);

    // continue to the next sprite
    txml_element = txml_element->NextSiblingElement();
  }

  // animation element
  else if(!strcmp(txml_element->Value(), "animation"))
  {
    // strip information from tag
    const char *name = txml_element->Attribute("name"),
               *texture = txml_element->Attribute("texture");
    iRect frame;
    int n_frames;
    bool success = (name && texture
      && (txml_element->QueryIntAttribute("x", &frame.x) == TIXML_SUCCESS)
      && (txml_element->QueryIntAttribute("y", &frame.y) == TIXML_SUCCESS)
      && (txml_element->QueryIntAttribute("w", &frame.w) == TIXML_SUCCESS)
      && (txml_element->QueryIntAttribute("h", &frame.h) == TIXML_SUCCESS)
      && (txml_element->QueryIntAttribute("n_frames", &n_frames) == TIXML_SUCCESS));

    if(!success)
      WARN_RTN("GraphicsManager::load_xml", "malformed animation tag", EXIT_FAILURE);

    // create the animation
    create_animation(texture, frame, n_frames, name);
  }

  // all clear!
  return EXIT_SUCCESS;
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
  // search for the resource
  str_id hash = numerise(name);
  TextureI i = textures.find(hash);
  // make sure that it is found
  if(i == textures.end())
    WARN_RTN("GraphicsManager::get_texture invalid identifier", name, NULL);

  // return the texture we recovered
  return (*i).second;
}


/// ANIMATIONS

int GraphicsManager::create_animation(const char* texture_name,
                          iRect frame, int n_frames, const char* animation_name)
{
  // attempt to retrieve the desired texture
  Texture* animation_texture = get_texture(texture_name);
  if(!animation_texture)
    WARN_RTN("Couldn't find animation source texture", texture_name, EXIT_FAILURE);

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
