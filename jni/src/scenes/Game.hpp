#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Scene.hpp"

class Game : public Scene
{
    /// METHODS
    public:
    // Constructors, destructors
    Game();
    ~Game();
    // Navigation
    Scene* previous();  // from Scene
    // Override
    int startup();
};

#endif // GAME_HPP_INCLUDED
