#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "SceneState.hpp"

class GameState;

#include "../gameplay/TunnelBG.hpp"
#include "../gameplay/TunnelFG.hpp"

#include "../gameplay/things/Thing.hpp"

class GameState : public SceneState
{
    /// ATTRIBUTES
    public:
    // Game objects
    TunnelBG parallax;
    TunnelFG obstacle;
    ThingList things;
    // Level boundary
    fRect level_bounds;

    /// METHODS
    public:
    // Constructors, destructors
    GameState();
    ~GameState();
    // Accessors
    int countThings(const char* name = NULL);
    void killThings(const char* name = NULL);
    void addThing(Thing*);
    void deleteThing(ThingIter* i);
    Thing* getHero();
    // Overrides SceneState
    int startup();
    int shutdown();
    int update();
    void draw();

    /// METHOD SUBROUTINES
    private:
    int load_things();
};

#endif // GAMESTATE_HPP_INCLUDED
