#include "GameState.hpp"

#include "../warn.hpp"
#include "../assert.hpp"            // for platform specific ASSERT macros
#include "../global.hpp"
#include "../numerise.hpp"
#include "../file.hpp"              // for loading assets
#include "../platform.hpp"          // for ASSET_PATH

//#include "../tinyxml/tinyxml.h"            // for loading game objects

#include "../gameplay/things/events/CollisionEvent.hpp" // for generating events
#include "../gameplay/things/events/BoundaryEvent.hpp"  // for generating events

/// CONSTRUCTORS, DESTRUCTORS

GameState::GameState() :
parallax(),
obstacle(),
things(),
resources(),
level_bounds(global::viewport)
{

}

GameState::~GameState()
{
}


/// ACCESSORS

int GameState::countThings(const char* name)
{
    if(name)
    {
        // count the Things of a given type
        str_id type = numerise(name);
        int result = 0;
        for(ThingIter i = things.begin(); i!= things.end(); i++)
            if (!(*i)->isDead() && (*i)->getType() == type)
                result++;

        return result;
    }
    else
        // return the total number of things
        return things.size();
}

void GameState::killThings(const char* name)
{
    if(name)
    {
        // kill Things of a given type
        str_id type = numerise(name);
        for(ThingIter i = things.begin(); i!= things.end(); i++)
            if (!(*i)->isDead() && (*i)->getType() == type)
                (*i)->die();
    }
    else
    {
        // kill all Things of a given type
        for(ThingIter i = things.begin(); i!= things.end(); i++)
            if(!(*i)->isDead())
                (*i)->die();
    }
}

void GameState::addThing(Thing* t)
{
    things.push_back(t);
}

void GameState::deleteThing(ThingIter* i)
{
    // Copy then advance the original iterator (to safety)
    ThingIter j = (*i);
    (*i)++;
    // Erase and remove the cell it was originally pointing to
    delete (*j);
    things.erase(j);
}

Thing* GameState::getHero()
{
    // Hero is always the first Thing in the list
    return (*(things.begin()));
}

ResourceManager* GameState::getResources()
{
    return resources;
}

/// OVERRIDES SCENE STATE

int GameState::startup()
{
    // Set the position of the mouse to the centre of the screen
    input.last_touch = global::viewport.getSize()/2;

    // Load external ressources
    resources = new ResourceManager();
    ASSERT(resources->load() == EXIT_SUCCESS, "Loading game resources");

    // All clear!
    return EXIT_SUCCESS;
}

int GameState::shutdown()
{
    // Destroy all game objects
    for(ThingIter i = things.begin(); i!= things.end(); i++)
        delete (*i);

    // Destroy all game resources
    resources->unload();
    delete resources;

    // All clear!
    return EXIT_SUCCESS;
}

int GameState::update()
{
  // Update background parallax tunnel
  parallax.update();

  // Update forground obstacle tunnel
  obstacle.update();

  // For each game object
  for(ThingIter i = things.begin(); i!= things.end(); )
  {
      // Update the object
      int update_result = (*i)->update(this);

      // Delete the object if nessecary
      switch(update_result)
      {
          case Thing::DELETE_ME:
              deleteThing(&i);
              continue;

          case Thing::LOSE_LEVEL:
              return EXIT_FAILURE;    /// FIXME

          case Thing::WIN_LEVEL:
              return EXIT_FAILURE;    /// FIXME
      }

      /// Check for collisions between this object and subsequent ones
      ThingIter j = i;
      // Unfortunately we can't write "j = i+1"
      for(j++; j!= things.end(); j++)
          CollisionEvent::generate((*i), (*j));

      /// Generate out of or intersect bounds events for the current object
      BoundaryEvent::generate((*i), &level_bounds);

      // manual iteration
      i++;
  }

  // All clear
  return EXIT_SUCCESS;
}

void GameState::draw()
{
  // Draw the background parallax tunnel
  parallax.draw();

  // Draw the foreground obstacle tunnel
  //obstacle.draw();

  // Draw all the game objects
  for(ThingIter i = things.begin(); i!= things.end(); i++)
      (*i)->draw();
}

/// SUBROUTINES

/*
int GameState::load_things()
{
    // Generate world XML file name based on number
    char file_name[32];
    WARN_IF((sprintf(file_name, "%sworld_%d.xml", ASSET_PATH_PATH, world_number) < 0),
            "Game::load_things", "Buffer too small to create formatted string");

    // Create the Tiny XML document
    TiXmlDocument doc;
    ASSERT(io::read_xml(file_name, &doc) == EXIT_SUCCESS, "Reading World XML");

    // Create local variables for searching document tree
    TiXmlHandle doc_handle(&doc);
    TiXmlElement* element;

    // Get a handle on the root world element
    element = doc_handle.FirstChildElement("World").Element();
    TiXmlHandle wld_handle = TiXmlHandle(element);

    /// FIND THE REQUESTED LEVEL WITHIN THE FILE
    element = wld_handle.FirstChild("Level").Element();
    while(element)
    {
        // get this element's 'number' attribute
        int n = 0;
        WARN_IF(element->QueryIntAttribute("number", &n) != TIXML_SUCCESS,
                "Game::load_things", "Level with no number attribute");

        // stop if it's the right one
        if(n == (int)level_number)
            break;
        // otherwise continue
        element = element->NextSiblingElement();
    }
    // make sure that the level was found
    ASSERT(element, "Finding level in world file");

    /// LOAD THE GAME OBJECTS FROM THE LEVEL TAG
    // create the hero (always the first element in the list)
    Thing* hero = resources->instantiate("hero",
                    (V2f)global::viewport.getSize() * V2f(0.5, 0.9));

    addThing(hero);
    // create other object
    element = element->FirstChildElement("Object");
    while(element)
    {
        // get normalised position
        V2f position;
        element->QueryDoubleAttribute("x", &position.x);
        element->QueryDoubleAttribute("y", &position.y);
        // convert it to a position within the current playing field
        position *= (V2f)global::viewport.getSize();
        // get type
        const char* type = element->Attribute("type");
        // create object
        Thing* new_thing = resources->instantiate(type, position);
        if(new_thing)
            addThing(new_thing);

        else
            WARN("Game::load_things","skipped unknown type");

        // continue to the next element
        element = element->NextSiblingElement();
    }

    // all good
    return EXIT_SUCCESS;
}
*/
