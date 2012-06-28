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
#ifndef GRAPHIC_HPP_INCLUDED
#define GRAPHIC_HPP_INCLUDED

#include "Texture.hpp"
#include "../math/Rect.hpp"

class Graphic
{
    /// ATTRIBUTES
    protected:
    Texture* texture;
    iRect frame; // the source area of

    /// METHODS
    public:
    // constructors, destructor
    Graphic();
    // main methods
    void init(Texture* init_texture, iRect init_frame);
    // accessors
    Texture* getTexture();
    iRect getFrame() const;
};

#endif // GRAPHIC_HPP_INCLUDED
