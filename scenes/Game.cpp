#include "Game.hpp"

#include "../file.hpp"          // ASSET_PATH
#include "../assert.hpp"        // ASSET_PATH
#include "MainMenu.hpp"         // previous
#include "GameState.hpp"


Game::Game() :
Scene(new GameState())
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
