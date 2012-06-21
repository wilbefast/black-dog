#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "Scene.hpp"

#include "Button.hpp"

class MainMenu : public Scene
{
    /// METHODS
    public:
    // Graphical elements
    Texture* texture;
    fRect title_src, title_dest;
    // Constructors, destructors
    MainMenu();
    ~MainMenu();
    int startup();
    int shutdown();
    // Executed each frame
    int update(Scene** next, float delta);
    void draw();
    // Back to previous scene
    Scene* previous();

};

#endif // MAINMENU_HPP_INCLUDED
