#ifndef ANIMATEDELEMENT_HPP_INCLUDED
#define ANIMATEDELEMENT_HPP_INCLUDED

#include "GraphicElement.hpp"
#include "../../../graphics/Animation.hpp"

class AnimatedElement : public GraphicElement
{
    /// ATTRIBUTES
    private:
    float frame_current;
    float frame_speed;

    /// METHODS
    public:
    // contructors, destructors
    AnimatedElement(Thing* init_owner);
    ~AnimatedElement();
    // accessors
    void setFrame(float new_frame);
    void setRandFrame();
    bool setSprite(Animation* new_sprite, float new_speed = 0);
    // overrides
    int update(GameState* context);     // ThingElement
    void draw();                        // ThingElement

    /// SUBROUTINES
    private:
    void loopAnim();

};

#endif // ANIMATEDELEMENT_HPP_INCLUDED
