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
#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "SDL.h"

#include "platform.hpp"
#include "scenes/Scene.hpp"

class Application
{
    /// FUNCTIONS
public:
    static V2i normaliseTouch(SDL_TouchID, V2i touch);

    /// CONSTANTS
    private:
    enum
    {
        CONTINUE,
        BACK,
        EXIT
    };

    /// ATTRIBUTES
private:
    // We might need to force cleanup upon destruction
    bool initialised;
    // Window and OpenGL context
    SDL_Window* window;
    SDL_GLContext context;
    // Timing
    int prev_tick, this_tick, next_tick;
    // Object containing all the game-related data
    Scene* scene;

    /// CONSTRUCTOR & DESTRUCTOR
public:
    Application(Scene* first_scene);
    ~Application();

    /// METHODS
public:
    int startup();
    int shutdown();
    // Perform a single application step, return
    int run();


    /// SUB-METHODS (called by other methods)
private:
    int startSDL();     // Create window and GL context
    int startGL();      // Configure GL itself
    void draw();
    // Regulate the number of frames per second, pausing only if need be
    void wait();
    // Deal with input messages, return false if an exit event is encountered
    int treatEvents();
    // Switch to a new scene, freeing the old and starting the new
    int setScene(Scene*);
};

#endif // APPLICATION_HPP_INCLUDED
