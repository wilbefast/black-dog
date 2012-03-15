#ifndef COLLIDERELEMENT_HPP_INCLUDED
#define COLLIDERELEMENT_HPP_INCLUDED

class ColliderElement;

#include "ThingElement.hpp"
#include "../../../Rect.hpp"

class ColliderElement : public ThingElement
{
    /// ATTRIBUTES
    private:
    fRect hitbox;

    /// METHODS
    public:
    // constructors, destructors
    ColliderElement(Thing* init_owner, V2f size, V2f offset = V2f(0,0));
    ColliderElement(const ColliderElement& src);
    // main methods
    bool isColliding(ColliderElement* other, V2i* side = NULL) const;
    bool isOutside(fRect* bounds, V2i* side = NULL) const;
    bool isLeaving(fRect* bounds, V2i* side = NULL) const;
    bool doesContain(V2f point) const;
    // accessors
    fRect getOffsetBox() const;
    V2i boundarySide(fRect* bounds) const;
    V2i collisionSide(ColliderElement* other) const;

};

#endif // COLLIDERELEMENT_HPP_INCLUDED
