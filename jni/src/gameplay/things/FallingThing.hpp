#ifndef FALLINGTHING_HPP_INCLUDED
#define FALLINGTHING_HPP_INCLUDED

#include "Thing.hpp"

#include "elements/AnimatedElement.hpp"
#include "elements/MovementElement.hpp"

class FallingThing : public Thing
{
  /// CONSTANTS
private:
  static const float X_SPEED = 3.0f;

  /// ATTRIBUTES
private:
  AnimatedElement graphic;
  MovementElement movement;

  /// METHODS
public:
  // creation, destruction
  FallingThing(V2i _position, const char* name, Animation* loop,
              float loop_speed, float gravity = 0.0f, float max_speed = -1);
  // overrides Thing
  int update(GameState*, float delta);
  void draw();
};

#endif // FALLINGTHING_HPP_INCLUDED
