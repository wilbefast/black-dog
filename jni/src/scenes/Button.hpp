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
#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "../graphics/Texture.hpp"
#include "../math/Rect.hpp"
#include "../resources/numerise.hpp"

class Button;

#include <list>

typedef std::list<Button*> ButtonSet;
typedef ButtonSet::iterator ButtonIter;

class Button
{
    /// ATTRIBUTES
    private:
    str_id tag;
    Texture texture;
    fRect destination;
    fRect source_off;
    fRect source_on;
    bool pressed, hovered;

    /// METHODS
    public:
    // constructors, destructors
    Button(const char* name, Texture init_texture, fRect init_destination,
               fRect init_source);
    Button(str_id init_tag, Texture init_texture, fRect init_destination,
           fRect init_source);
    ~Button();
    void correctAspect(fRect init_src, fRect init_dest);
    // each frame
    void draw();
    // accessors
    str_id getTag() const;
    bool contains(V2f position) const;
    bool press(V2f position, bool clicking);
};

#endif // BUTTON_HPP_INCLUDED
