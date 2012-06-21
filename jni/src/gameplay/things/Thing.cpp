#include "Thing.hpp"

#include "../../resources/numerise.hpp"                          // for hash function

#include "../../assert.hpp"
#include "../../warn.hpp"

#include "elements/ColliderElement.hpp"

/// METHODS

// Constructors, destructors
Thing::Thing(V2f init_position, const char* type_name) :
type(numerise(type_name)),
dead(false),
position(init_position),
events()
{
}

Thing::Thing(V2f init_position, str_id init_type) :
type(init_type),
dead(false),
position(init_position),
events()
{
}

Thing::Thing(Thing const& source) :
type(source.type),
position(source.position),
events()
{
}

Thing::~Thing()
{
}

// Main methods

void Thing::addEvent(ThingEvent* new_event)
{
    events.push_back(new_event);
}

// Accessors

bool Thing::isDead() const
{
    return dead;
}

const EventList* Thing::getEvents()
{
    return &events;
}

void Thing::deleteEvents()
{
    // Delete the events contained in the list, not the list itself
    for(EventIter i = events.begin(); i != events.end(); i++)
        delete (*i);
    events.clear();
}

str_id Thing::getType() const
{
    return type;
}

V2f Thing::getPosition() const
{
    return position;
}

void Thing::move(V2f translation)
{
    position += translation;
}

void Thing::moveTo(V2f new_position)
{
    position = new_position;
}


// Overridden

void Thing::die()
{
    // instance will be deleted at the *end* of its next update
    dead = true;
}

void Thing::draw()
{
    // overridden if visible
}

int Thing::update(GameState* context, float delta)
{
  // clear all events from the list
  deleteEvents();

  // should still be called at end of update, even if overridden
  if(dead)
    return GameState::DELETE_ME;
  else
    return GameState::CONTINUE;
}

bool Thing::isColliding(Thing* other, V2i* side)
{
    // must have a ColliderElement to collide
    if(!body || !other->body)
        return false;
    else
        return body->isColliding(other->body, side);
}

bool Thing::isOutside(fRect* bounds, V2i* side)
{
    // must have a ColliderElement to be outside boundaries
    if(!body)
        return false;
    else
        return body->isOutside(bounds, side);
}

bool Thing::isLeaving(fRect* bounds, V2i* side)
{
    // must have a ColliderElement to intersect boundaries
    if(!body)
        return false;
    else
        return body->isLeaving(bounds, side);

}


/// SUBROUTINES

void Thing::consumeEvent(EventIter* i)
{
    // The function is called during list iteration, so steps must be taken to
    // ensure that it is "safe".

    // list: [x, i, y], next cell will be 'y'

    EventIter j = (*i);
    // list: [x, i=j, y]
    (*i)++;
    // list: [x, j, i=y]

    delete (*j);
    events.erase(j);
    // list: [x, i=y], 'i' is now equal to 'y'
}

