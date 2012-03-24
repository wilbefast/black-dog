#ifndef GRAPHICSMANAGER_HPP_INCLUDED
#define GRAPHICSMANAGER_HPP_INCLUDED

#include <map>
#include "numerise.hpp"         // for str_id

#include "../graphics/Texture.hpp"
#include "../graphics/Animation.hpp"

typedef std::map<str_id, Texture*> TextureMap;
typedef TextureMap::iterator TextureI;
typedef std::map<str_id, Animation*> AnimationMap;
typedef AnimationMap::iterator AnimationI;

class GraphicsManager
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
  // textures
  int load_texture(const char* source_file, const char* name);
  Texture* get_texture(const char* name);
  // animation
};

#endif // GRAPHICSMANAGER_HPP_INCLUDED
