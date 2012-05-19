#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "SceneState.hpp"

class GameState;

#include "../gameplay/things/Thing.hpp"

class GameState : public SceneState
{
    /// NESTING
public:
    // FIXME -- add an "Updatable" interface class
    enum update_result
    {
        CONTINUE,
        LOSE_LEVEL,
        WIN_LEVEL,
        DELETE_ME
    };

    /// ATTRIBUTES
private:
    // Game objects
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
    virtual int update();
    virtual void draw();
};

#endif // GAMESTATE_HPP_INCLUDED
