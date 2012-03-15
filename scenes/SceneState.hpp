#ifndef SCENESTATE_HPP_INCLUDED
#define SCENESTATE_HPP_INCLUDED

//#include "numerise.hpp"     // str_id
#include "Button.hpp"
#include "../V2.hpp"

class SceneState
{
    /// NESTING
    public:
    class Input
    {
        public:
        // attributes
        V2u last_touch;
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
    virtual int update();
    virtual void draw();
    // Accessors
    Input* getInput();
    void setCursor(V2u new_last_touch, bool new_clicking);
    str_id releasedOnButton();
    bool newClick() const;
};

#endif // SCENESTATE_HPP_INCLUDED
