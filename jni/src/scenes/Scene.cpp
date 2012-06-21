#include "Scene.hpp"

#include "../global.hpp"
#include "../assert.hpp"
#include "../warn.hpp"

/// CONSTRUCTORS

Scene::Scene(SceneState* init_state) :
buttons()
{
    state = init_state ? init_state : new SceneState();
}

Scene::~Scene()
{
}

/// VIRTUAL

 void Scene::draw()
 {
    // Draw the buttons
    for(ButtonIter i = buttons.begin(); i != buttons.end(); i++)
        (*i)->draw();

    // Draw anything dynamic
    state->draw();
 }

int Scene::update(Scene** next, float delta)
 {
    // Either continue (value of next is ignored) or go back to previous
    (*next) = previous();

    // Update buttons based on touch position
    for(ButtonIter i = buttons.begin(); i != buttons.end(); i++)
        if((*i)->press(state->input.last_hover, state->input.clicking))
        {
            // Save the first button we're touching and break
            state->input.last_button = (*i);
            break;
        }

    // update anything dynamic, go back to previous scene if nessecary
    if(state->update(delta) == SceneState::EXIT)
        return Scene::CHANGE;

    //continue
    return Scene::NO_CHANGE;
 }

 int Scene::startup()
 {
    // Start the state if applicable
    ASSERT(state->startup() == EXIT_SUCCESS, "Scene initialising state");

    // All clear
    return EXIT_SUCCESS;
 }

 int Scene::shutdown()
 {
    // Delete buttons
    for(ButtonIter i = buttons.begin(); i != buttons.end(); i++)
        delete (*i);

    // Delete anything dynamic
    ASSERT(state->shutdown() == EXIT_SUCCESS, "Scene shutting down state");
    delete state;

    // All clear
    return EXIT_SUCCESS;
 }

Scene* Scene::previous()
{
    return NULL;
}

/// ACCESSORS

void Scene::addButton(Button* new_button)
{
    buttons.push_back(new_button);
}

SceneState* Scene::getState()
{
    return state;
}

/// FUNCTIONS

int Scene::splitRect(fRect src, fRect result[], V2u n_divisions,
                         double scale)
{
    // Compute the split rectangle size
    fRect split = src / V2f(n_divisions);

    // Create each of the rectangles
    for(V2u i(0,0); i.y < n_divisions.y; i.y++)
        for(i.x = 0; i.x < n_divisions.x; i.x++)
        {
            // Create and scale
            fRect new_rect = fRect(split + V2f(i)*split.getSize());
            new_rect.stretch_centered(scale);
            // Add to the resulting unroled matrix
            result[i.x + (i.y)*n_divisions.x] = new_rect;
        }
    return EXIT_SUCCESS;
}

fRect Scene::squashRect(fRect src, V2f amount)
{
    // Squash horizontally
    if(amount.x > 0)
    {
        src.x += amount.x;
        src.w -= amount.x;
    }
    else
        src.w += amount.x;

    // Squash vertically
    if(amount.y > 0)
    {
        src.y += amount.y;
        src.h -= amount.y;
    }
    else
        src.h += amount.y;

    // Return result
    return src;
}
