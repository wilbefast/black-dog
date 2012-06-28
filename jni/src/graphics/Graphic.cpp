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
