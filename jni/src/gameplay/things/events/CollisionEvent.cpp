#include "CollisionEvent.hpp"

/// FUNCTIONS

void CollisionEvent::generate(Thing* a, Thing* b)
{
    // Save the side upon which the event occured
    V2i side;

    // Check for collisions
    if(!a->isDead() && !b->isDead() && a->isColliding(b, &side))
    {
        // Generate collision events
        a->addEvent(new CollisionEvent(b, side));
        b->addEvent(new CollisionEvent(a, -side));
    }
}

/// METHODS

// constructors, destructor

CollisionEvent::CollisionEvent(Thing* init_other, V2i init_side) :
ThingEvent("collision"),
other(init_other),
collision_side(init_side)
{
}

// accessors
Thing* CollisionEvent::getOther()
{
    return other;
}

V2i CollisionEvent::getSide() const
{
    return collision_side;
}
