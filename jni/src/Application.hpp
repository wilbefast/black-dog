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
    int this_tick, next_tick, missed_ticks;
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

    /// OVERRIDDEN
protected:
    virtual int loadResources();
};

#endif // APPLICATION_HPP_INCLUDED
