#ifndef THINGELEMENT_HPP_INCLUDED
#define THINGELEMENT_HPP_INCLUDED

class ThingElement;

#include "../Thing.hpp"

class ThingElement
{
    /// ATTRIBUTES
    protected:
    Thing* owner;

    /// METHODS
    public:
    // constructors, destructor
    ThingElement(Thing* init_owner);
    virtual ~ThingElement();
    // overriden
    virtual int update(GameState* context);
    virtual void draw();

};

#endif // THINGELEMENT_HPP_INCLUDED
