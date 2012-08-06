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
#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "../graphics/Texture.hpp"
#include "../math/V2.hpp"

#include "Button.hpp"
#include "SceneState.hpp"

class Scene
{
    /// CONSTANTS
    public:
    enum UpdateResult
    {
        NO_CHANGE,
        CHANGE
    };

    /// FUNCTIONS
    public:
    static int splitRect(fRect src, fRect result[], V2u n_divisions,
                          double scale = 1.0);
    static fRect squashRect(fRect src, V2f amount);

    /// ATTRIBUTES
    protected:
    // Interactive areas
    ButtonSet buttons;
    // Dynamic attributes
    SceneState* state;

    /// METHODS
    public:
    // Constructors, destructors
    Scene(SceneState* init_state = NULL);
    virtual ~Scene();
    // Executed each frame
    virtual void draw();    // pure virtual
    virtual int update(Scene** next, float delta);  // pure virtual
    // Manual creation and destruction
    virtual int startup();
    virtual int shutdown();
    // Return to previous scene
    virtual Scene* previous();
    // Accessors
    SceneState* getState();
    void addButton(Button*);

};

#endif // SCENE_HPP_INCLUDED
