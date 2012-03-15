#ifndef COLLISIONEVENT_HPP_INCLUDED
#define COLLISIONEVENT_HPP_INCLUDED

#include "ThingEvent.hpp"
#include "../Thing.hpp"

class CollisionEvent : public ThingEvent
{
    /// FUNCTIONS
    public:
    static void generate(Thing* a, Thing* b);

    /// ATTRIBUTES
    private:
    Thing* other;
    V2i collision_side;

    /// METHODS
    public:
    // constructors, destructor
    CollisionEvent(Thing* other, V2i side);
    // accessors
    Thing* getOther();
    V2i getSide() const;
};

#endif // COLLISIONEVENT_HPP_INCLUDED
