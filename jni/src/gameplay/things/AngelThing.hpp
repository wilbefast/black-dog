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
#ifndef ANGELTHING_HPP_INCLUDED
#define ANGELTHING_HPP_INCLUDED

#include "Thing.hpp"

// attributes
#include "../../graphics/Animation.hpp"
#include "elements/AnimatedElement.hpp"
#include "elements/MovementElement.hpp"
#include "elements/ResourceElement.hpp"
#include "elements/TimerElement.hpp"

class AngelThing : public Thing
{
  /// NESTING
public:
  class State
  {
  private:
    // constants
    // class namespace variables
    static unsigned int next_id;
  public:
    // attributes
    const float gravity, speed_max;
    const unsigned int id;
    // methods
    State(float _gravity, float _speed_max);
    bool operator==(const State& other) const;
  };

  /// CONSTANTS
public:
  // numeric constants
  static const float THRUST;        // vertical speed of flapping wings
  static const float BOUNCE_BACK;
  static const float BOUNCE_DOWN;
  static const float BOUNCE_UP;
  static const float SPEED_H_INC;   // horizontal speed towards the right
  static const float SPEED_H_MAX;
  static const float SPEED_H_ORB;
  static const float FRICTION;
  static const int MAX_FEATHERS = 8;
  static const int MAX_ORBS = 4;
  static const int FEATHER_INTERVAL = 72;
  static const int ORB_USE_INTERVAL = 36;
  static const int ORB_COLLISION_PENALTY = 2;
  static const int STUN_DURATION = 20;
  static const int SPRITE_W = 112;
  static const int SPRITE_H = 54;
  static const int HITBOX_W = 8;
  static const int HITBOX_H = 16;
  static const int MAX_SNAP = 32;
  static const int MAX_X = 148;
  // states
  static const State FLAPPING, GLIDING, FALLING, STUNNED, BOOSTING, DEAD;

  /// ATTRIBUTES
private:
  State const* state;
  AnimatedElement graphic;
  MovementElement movement;
  ResourceElement feathers, orbs;
  TimerElement stun_timer, feather_timer, orb_use_timer;
  float furthest_x;

  /// METHODS
public:
  // creation
  AngelThing(V2i _position);
  // overrides
  void draw();
  int update(GameState* context, float delta);
  // query
  V2f getPrevPosition() const;
  int countFeathers() const;
  int countOrbs() const;
  float getFurthestX() const;

  /// SUBROUTINES
private:
  void setState(AngelThing::State const& new_state, GameState* context);
  int treatEvent(ThingEvent* event, GameState* context);
  int treatInput(GameState* context);
  int checkCollision(GameState* context);
};

#endif // ANGELTHING_HPP_INCLUDED
