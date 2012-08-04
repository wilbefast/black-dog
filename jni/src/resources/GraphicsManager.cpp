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

#include "tinyxml/tinyxml_dump.h"
#include "file.hpp"
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
  // don't start twice!
  if(started)
    WARN_RTN("GraphicsManager::startup","already started!", EXIT_SUCCESS);

  // load graphics
  ASSERT(load_xml(GET_ASSET("graphics.xml")) == EXIT_SUCCESS,
        "Loading graphical assets based on 'graphics.xml'");

  // All good!
  started = true;
  return EXIT_SUCCESS;
}

int GraphicsManager::load_xml(const char* xml_file)
{
  // pass string to the TinyXML document
  TiXmlDocument doc;
  ASSERT_AUX(io::read_xml(xml_file, &doc) == EXIT_SUCCESS,
            "Opening graphics pack XML file", doc.ErrorDesc());

  // create local variables for searching document tree
  TiXmlHandle doc_handle(&doc);
  TiXmlElement* element = NULL;

  // the root is a 'graphics' tag
  element = doc_handle.FirstChildElement("graphics").Element();
  TiXmlHandle root_handle = TiXmlHandle(element);

  // load textures
  element = root_handle.FirstChild("texture_list").FirstChild().Element();

  while(element)
  {
    // get the name of the texture and deduce its filename
    const char* name = element->Attribute("name");

    if(!name)
      WARN_RTN("GraphicsManager::load_xml", "malformed texture tag", EXIT_FAILURE);
    string filename(ASSET_PATH);
      filename.append(name);
      filename.append(".png");

    // load the texture
    load_texture(filename.c_str(), name);

    // continue to the next sprite
    element = element->NextSiblingElement();
  }

  // load animations
  element = root_handle.FirstChild("animation_list").FirstChild().Element();
  while(element)
  {
    // strip information from tag
    const char *name = element->Attribute("name"),
               *texture = element->Attribute("texture");
    iRect frame;
    int n_frames;
    bool success = (name && texture
      && (element->QueryIntAttribute("x", &frame.x) == TIXML_SUCCESS)
      && (element->QueryIntAttribute("y", &frame.y) == TIXML_SUCCESS)
      && (element->QueryIntAttribute("w", &frame.w) == TIXML_SUCCESS)
      && (element->QueryIntAttribute("h", &frame.h) == TIXML_SUCCESS)
      && (element->QueryIntAttribute("n_frames", &n_frames) == TIXML_SUCCESS));

    if(!success)
      WARN_RTN("GraphicsManager::load_xml", "malformed animation tag", EXIT_FAILURE);

    // create the animation
    create_animation(texture, frame, n_frames, name);

    // continue to the next sprite
    element = element->NextSiblingElement();
  }

  // all good
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
