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
        CHANGE,
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
    virtual int update(Scene** next);  // pure virtual
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
