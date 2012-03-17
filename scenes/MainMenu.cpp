#include "MainMenu.hpp"

#include "../global.hpp"
#include "../warn.hpp"
#include "../assert.hpp"
#include "../platform.hpp"
#include "../file.hpp"

#include "Game.hpp"

/// CONSTRUCTORS, DESTRUCTORS

MainMenu::MainMenu() :
Scene(),
texture_file(GET_ASSET("main_menu.png")),
texture(),
title_src(0.0f, 0.0f, 0.0f, 0.0f),
title_dest(0.0f, 0.0f, 0.0f, 0.0f)
{
}

MainMenu::~MainMenu()
{
}

int MainMenu::startup()
{
    // pass up hierarchy
    ASSERT(Scene::startup() == EXIT_SUCCESS, "MainMenu generic startup");

    // load the texture
    ASSERT(texture.load(texture_file) == EXIT_SUCCESS,
              "MainMenu loading texture");

    /// 1. TITLE IMAGE (TOP THIRD)
    // set the area of the screen to use (the top third)
    fRect top_third = fRect(global::viewport) / V2f(1,3);
    // set the area of texture to draw
    title_src = fRect(0, 0, 320, 150);
    // maintain aspect ratio
    title_dest.setRatio(title_src.getRatio());
    // centre the title image within the top area of the screen
    title_dest.centreWithin(top_third);

    /// 2. BUTTONS (BUTTON SIX NINTHS)
    // set the area of the screen to use (bottom two top thirds)
    fRect bottom_thirds = squashRect(global::viewport, V2f(0, top_third.h));
    fRect top_ninths = bottom_thirds / V2f(1,3);
    fRect mid_ninths = top_ninths + V2f(0, top_ninths.h);
    fRect low_ninths = mid_ninths + V2f(0, mid_ninths.h);
    // the top and bottom buttons are smaller than the middle one
    top_ninths.stretch_centered(0.7);
    mid_ninths.stretch_centered(0.8);
    low_ninths.stretch_centered(0.7);
    // set the area of texture to draw (on top of eachother)
    fRect play_src(0, title_src.h, 160, 70);
    fRect exit_src = play_src + V2f(0, play_src.h);
    fRect options_src(0, exit_src.y + exit_src.h, 256, 70);
    // add the buttons to the scene
    buttons.push_back(new Button("play", texture, top_ninths, play_src));
    buttons.push_back(new Button("options", texture, mid_ninths, options_src));
    buttons.push_back(new Button("exit", texture, low_ninths, exit_src));

    /// 3. ALL CLEAR!
    return EXIT_SUCCESS;
}

int MainMenu::update(Scene** next)
{
    // Pass up hierarchy
    Scene::update(next);

    // Move to the next screen on click
    str_id button_tag;
    if((button_tag = state->releasedOnButton()))
    {
        // select world
        if(button_tag == numerise("play"))
            (*next) = new Game();
        // change options
        else if(button_tag == numerise("options"))
            return true; /// FIXME
        // exit the game
        else if(button_tag == numerise("exit"))
            (*next) = NULL; // exit

        // change scene
        return Scene::CHANGE;
    }
    else
        // keep same scene
        return Scene::NO_CHANGE;
}

Scene* MainMenu::previous()
{
    return NULL;
}
