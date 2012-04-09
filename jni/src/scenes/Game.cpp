#include "Game.hpp"

#include "../resources/file.hpp"           // ASSET_PATH
#include "../assert.hpp"            // ASSERT
#include "MainMenu.hpp"             // previous scene

#include "BlackDogState.hpp"


Game::Game() :
Scene(new BlackDogState())
{
}

int Game::startup()
{
    ASSERT(Scene::startup() == EXIT_SUCCESS, "Game generic startup");

    return EXIT_SUCCESS;
}

Game::~Game()
{
}

Scene* Game::previous()
{
    return new MainMenu();
}
