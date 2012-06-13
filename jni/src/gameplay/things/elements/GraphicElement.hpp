#ifndef GRAPHICELEMENT_HPP_INCLUDED
#define GRAPHICELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../graphics/Graphic.hpp"

class GraphicElement : public ThingElement
{
    /// ATTRIBUTES
    protected:
    Graphic* sprite;
    fRect destination;
    V2f offset, size;
    float angle;

    /// METHODS
    public:
    // contructors, destructors
    GraphicElement(Thing* init_owner, V2f _size = V2f(0.0f, 0.0f),
                                      V2f _offset = V2f(0.0f, 0.0f));
    ~GraphicElement();
    // accessors
    void setAngle(float new_angle);
    bool setSprite(Graphic* new_sprite);
    // overrides
    virtual int update(GameState* context);     // ThingElement
    virtual void draw();                        // ThingElement
    // subroutines
    protected:
    void centreFrame();

};

#endif // GRAPHICELEMENT_HPP_INCLUDED
