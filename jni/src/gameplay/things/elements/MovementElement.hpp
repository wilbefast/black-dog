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
#ifndef MOVEMENTELEMENT_HPP_INCLUDED
#define MOVEMENTELEMENT_HPP_INCLUDED

#include "float.h"
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
    MovementElement(Thing* init_owner, float init_speed_max = FLT_MAX,
                    float init_friction = 1,
                    float init_speed_min = DEFAULT_SPEED_MIN);
    ~MovementElement();
    // main methods
    void springTowards(V2f target_position, float spring_constant);
    void add_springTowards(V2f target_position, float spring_constant);
    void moveTowards(V2f target_position, float speed);
    void add_moveTowards(V2f target_position, float speed);
    void add_speedScalar(float speed);
    void bounce(V2i collision_side);
    int update(GameState* context, float delta);
    // modification
    void setSpeed_scalar(float new_speed_scalar);
    void setSpeed(V2f new_speed);
    void setSpeedX(float new_speed);
    void setSpeedY(float new_speed);
    void addSpeed(V2f force);
    void addSpeedX(float force);
    void addSpeedY(float force);
    void setSpeedMax(float _max_speed);
    // query
    float getSpeedX() const;
    float getSpeedY() const;
    V2f getSpeed() const;
    V2f getPrevPos() const;
    float getSpeed_scalar() const;
    float getAngle() const;

};

#endif // MOVEMENTELEMENT_HPP_INCLUDED
