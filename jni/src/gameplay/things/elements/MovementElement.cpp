/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "MovementElement.hpp"

#include "../events/ThingEvent.hpp"
#include "../../../math/wjd_math.hpp"           // for SQR

using namespace std;

// Constants

const float MovementElement::DEFAULT_SPEED_MIN = 0.06;

// Constructors, destructors

MovementElement::MovementElement(Thing* init_owner) :
ThingElement(init_owner),
speed(V2f(0,0)),
previous_position(owner->getPosition()),
speed_scalar(0),
angle(0)
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

void MovementElement::setSpeed(V2f new_speed)
{
  // Signal if starting to move
  if(!speed && new_speed)
    owner->addEvent(new ThingEvent("started_moving"));

  // Set the new speed
  speed = new_speed;

  // Cache absolute speed and angle
  speed_scalar = speed.getNorm();
  if(speed_scalar > 1)
    angle = speed.getAngle();
}

void MovementElement::setSpeed_scalar(float new_speed_scalar)
{
    setSpeed(speed/(speed.getNorm())*new_speed_scalar);
}

void MovementElement::setSpeedX(float new_speed)
{
  setSpeed(V2f(new_speed, speed.y));
}

void MovementElement::setSpeedY(float new_speed)
{
  setSpeed(V2f(speed.x, new_speed));
}

void MovementElement::addSpeedX(float force)
{
  setSpeed(V2f(speed.x + force, speed.y));
}

void MovementElement::addSpeedY(float force)
{
  setSpeed(V2f(speed.x, speed.y + force));
}

void MovementElement::addSpeed(V2f force)
{
    setSpeed(speed + force);
}

// Query

float MovementElement::getSpeedX() const
{
    return speed.x; // copy
}


float MovementElement::getSpeedY() const
{
    return speed.y; // copy
}


V2f MovementElement::getSpeed() const
{
    return speed; // copy
}

V2f MovementElement::getPrevPos() const
{
    return previous_position; // copy
}

float MovementElement::getSpeed_scalar() const
{
    return speed_scalar; // copy of cached value
}

float MovementElement::getAngle() const
{
    return angle; // copy of cached value
}

// Overrides

int MovementElement::update(GameState* context, float delta)
{
  // save previous position and then move
  previous_position = owner->getPosition();
  owner->move(speed*delta);

  // overrides insert friction, etc here

  // no interruption
  return SceneState::CONTINUE;
}
