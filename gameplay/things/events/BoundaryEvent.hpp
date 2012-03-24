#ifndef BOUNDARYEVENT_HPP_INCLUDED
#define BOUNDARYEVENT_HPP_INCLUDED

#include "ThingEvent.hpp"
#include "../../../math/V2.hpp"
#include "../../../math/Rect.hpp"

class Thing;

class BoundaryEvent : public ThingEvent
{
    /// FUNCTIONS
    public:
    static void generate(Thing* t, fRect* boundary);

    /// ATTRIBUTES
    private:
    V2i boundary_side;

    /// METHODS
    public:
    // constructor, destructors
    BoundaryEvent(const char* init_name, V2i init_side);
    // accessors
    V2i getSide() const;
};

#endif // BOUNDARYEVENT_HPP_INCLUDED
