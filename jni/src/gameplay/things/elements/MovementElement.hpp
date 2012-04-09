#ifndef MOVEMENTELEMENT_HPP_INCLUDED
#define MOVEMENTELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../scenes/GameState.hpp"

class MovementElement : public ThingElement
{
    /// CONSTANTS
    private:
    static const float DEFAULT_SPEED_MIN;

    /// ATTRIBUTES
    private:
    V2f speed;
    V2f previous_position;
    float speed_scalar; // scalars stored on speed change for quick access
    float angle;
    float speed_max;
    float speed_min;
    float friction;

    /// METHODS
    public:
    // constructors, destructors
    MovementElement(Thing* init_owner, float init_speed_max,
                    float init_friction = 0,
                    float init_speed_min = DEFAULT_SPEED_MIN);
    ~MovementElement();
    // main methods
    void springTowards(V2f target_position, float spring_constant);
    void add_springTowards(V2f target_position, float spring_constant);
    void moveTowards(V2f target_position, float speed);
    void add_moveTowards(V2f target_position, float speed);
    void add_speedScalar(float speed);
    void bounce(V2i collision_side);
    int update(GameState* context);
    // accessors
    V2f getSpeed() const;
    void setSpeed_scalar(float new_speed_scalar);
    void setSpeed(V2f new_speed);
    void addSpeed(V2f force);
    V2f getPrevPos() const;
    float getSpeed_scalar() const;
    float getAngle() const;

};

#endif // MOVEMENTELEMENT_HPP_INCLUDED
