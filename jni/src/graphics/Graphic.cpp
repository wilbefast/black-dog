#include "Graphic.hpp"

using namespace std;

// Constructors, destructors
Graphic::Graphic() :
texture(NULL)
{
}

// Main methods
void Graphic::init(Texture* init_texture, iRect init_frame)
{
  texture = init_texture;
  frame = init_frame;
}

// Accessors

Texture* Graphic::getTexture()
{
  return texture;
}

iRect Graphic::getFrame() const
{
  return frame;
}
