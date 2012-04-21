#include "MovementElement.hpp"

#include "../events/ThingEvent.hpp"
#include "../../../math/wjd_math.hpp"           // for SQR
#include "../../../global.hpp"                  // for DEFAULT_WINDOW_W/H

#include <iostream>

using namespace std;

// Constants

const float MovementElement::DEFAULT_SPEED_MIN = 0.06;

// Constructors, destructors

MovementElement::MovementElement(Thing* init_owner, float init_speed_max,
                                     float init_friction,
                                     float init_speed_min) :
ThingElement(init_owner),
speed(V2f(0,0)),
previous_position(owner->getPosition()),
speed_scalar(0),
angle(0),
speed_max(init_speed_max),
speed_min(init_speed_min),
friction(init_friction)
{
}

MovementElement::~MovementElement()
{
}

// Main methods

void MovementElement::springTowards(V2f target_position,
                                       float spring_constant)
{
    // Move towards target based on distance and speed factor
    setSpeed((target_position - owner->getPosition())*spring_constant);
}

void MovementElement::add_springTowards(V2f target_position,
                                       float spring_constant)
{
    // Move towards target based on distance and speed factor
    addSpeed((target_position - owner->getPosition())*spring_constant);
}

void MovementElement::moveTowards(V2f target_position, float force)
{
    // Move towards the target at a constant rate
    V2f move_vector = target_position - owner->getPosition();
    move_vector.setMagnitude(force);
    setSpeed(move_vector);
}

void MovementElement::add_moveTowards(V2f target_position, float force)
{
    // Move towards the target at a constant rate
    V2f move_vector = target_position - owner->getPosition();
    move_vector.setMagnitude(force);
    addSpeed(move_vector);
}

void MovementElement::add_speedScalar(float force)
{
    add_moveTowards(owner->getPosition()+speed, force);
}

void MovementElement::bounce(V2i collision_side)
{
    // jump back to previous position
    owner->moveTo(previous_position);

    // bounce opposite to wall
    collision_side *= -1;

    // maintain speed on axes that are not colliding
    if(!collision_side.x) collision_side.x = 1;
    if(!collision_side.y) collision_side.y = 1;

    // let's bounce!
    setSpeed((V2f)collision_side*speed);
}

// Modification

void MovementElement::setSpeed_scalar(float new_speed_scalar)
{
    setSpeed(speed/(speed.getNorm())*new_speed_scalar);
}

void MovementElement::setSpeed(V2f new_speed)
{
    // Signal if starting to move
    if(!speed && new_speed)
        owner->addEvent(new ThingEvent("started_moving"));

    // Set the new speed
    speed = new_speed;

    // Check terminal velocity
    speed_scalar = speed.getNorm();
    if(speed_scalar > speed_max)
        speed = (speed/speed_scalar)*speed_max; // normalise and remultiply

    // Reset movement angle, used for quick accesses
    if(speed_scalar > 1)
        angle = speed.getAngle();
}

void MovementElement::addSpeed(V2f force)
{
    setSpeed(speed + force);
}

void MovementElement::setSpeedMax(float _speed_max)
{
  speed_max = _speed_max;
}


// Query

V2f MovementElement::getSpeed() const
{
    return speed;
}

V2f MovementElement::getPrevPos() const
{
    return previous_position;
}

float MovementElement::getSpeed_scalar() const
{
    return speed_scalar;
}

float MovementElement::getAngle() const
{
    return angle;
}

// Overrides

int MovementElement::update(GameState* context)
{
    // move
    previous_position = owner->getPosition();
    owner->move(speed);

    // slow down
    if(friction)
        speed /= (float)friction;

    // cap minimum speed, generate event if stopping
    if(speed && (abs(speed.x) < speed_min) && (abs(speed.y) < speed_min))
    {
        speed.x = speed.y = 0;
        owner->addEvent(new ThingEvent("stopped_moving"));
    }

    // no interruption
    return SceneState::CONTINUE;
}
