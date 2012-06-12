#include "SceneState.hpp"

#include <stdlib.h>

/// CONSTRUCTORS DESTRUCTORS
SceneState::SceneState() :
input()
{
}

SceneState::~SceneState()
{
}

/// STARTUP AND SHUTDOWN

int SceneState::startup()
{
    return EXIT_SUCCESS;
}

int SceneState::shutdown()
{
    return EXIT_SUCCESS;
}

/// UPDATE AND DRAW

int SceneState::update()
{
    // Nothing to report
    return EXIT_SUCCESS;
}

void SceneState::draw()
{
}

/// ACCESSORS

SceneState::Input* SceneState::getInput()
{
    return &input;
}

void SceneState::setCursor(V2u new_cursor_position, bool new_clicking)
{
    // save the previous state
    input.clicking_previous = input.clicking;
    // set to the new state
    input.last_hover = new_cursor_position;
    if((input.clicking = new_clicking))
        input.last_touch = new_cursor_position;
}

str_id SceneState::releasedOnButton()
{
    if(!input.clicking && input.clicking_previous && input.last_button
    && input.last_button->contains(input.last_touch))
    {
        input.clicking_previous = false; // clear input
        return input.last_button->getTag();
    }
    else
        return 0;
}

bool SceneState::newClick() const
{
    return (!input.clicking && input.clicking_previous);
}
