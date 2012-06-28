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
#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "../platform.hpp"     // Needed for GLuint
#include "../math/V2.hpp"           // Needed for V2i
#include "../math/Rect.hpp"         // Needed for iRect

class Texture
{
    /// ATTRIBUTES
    public:
    GLuint handle;
    private:
    iRect area; // size of the texture

    /// METHODS
    public:
    iRect getArea();
    int load(const char* filename);
    int unload();
    void draw(const fRect* source_pointer,
              const fRect* destination_pointer,
              float angle = 0.0);

};

#endif // TEXTURE_HPP_INCLUDED
