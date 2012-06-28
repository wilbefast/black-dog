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
#ifndef SCENESTATE_HPP_INCLUDED
#define SCENESTATE_HPP_INCLUDED

//#include "numerise.hpp"     // str_id
#include "Button.hpp"
#include "../math/V2.hpp"

class SceneState
{
    /// NESTING
    public:
    class Input
    {
        public:
        // attributes
        V2u last_touch, last_hover;
        bool clicking, clicking_previous;
        Button* last_button;
        // constructor
        Input() : clicking(false), clicking_previous(false), last_button(NULL)
        {}
    };

    enum UpdateResult
    {
        CONTINUE,
        EXIT,
    };

    /// FRIENDS
    friend class Scene;

    /// ATTRIBUTES
    protected:
    // Input management
    Input input;

    /// METHODS
    public:
    // Constructors, destructors
    SceneState();
    virtual ~SceneState();
    // Explicit startup code, if needed
    virtual int startup();
    virtual int shutdown();
    // Update and draw dynamic objects, if needed
    virtual int update(float delta);
    virtual void draw();
    // Accessors
    Input* getInput();
    void setCursor(V2u new_cursor_position, bool new_clicking);
    str_id releasedOnButton();
    bool newClick() const;
};

#endif // SCENESTATE_HPP_INCLUDED
