#ifndef ASYMETRICALMOVEMENTELEMENT_HPP_INCLUDED
#define ASYMETRICALMOVEMENTELEMENT_HPP_INCLUDED

#include "MovementElement.hpp"

class AsymetricalMovementElement : public MovementElement
{
  /// ATTRIBUTES
private:
  // pseudo-constant set upon creation of object
  V2f speed_max;
  V2f speed_min;
  V2f friction;

  /// METHODS
public:
  // creation, destruction
  AsymetricalMovementElement(Thing* _owner, V2f _speed_max,
                  V2f _friction = V2f(1.0f, 1.0f),
                  V2f _speed_min = V2f(DEFAULT_SPEED_MIN, DEFAULT_SPEED_MIN));
  // main methods
  virtual int update(GameState* context, float delta);
  // modification
  virtual void setSpeed(V2f new_speed);
};

#endif // ASYMETRICALMOVEMENTELEMENT_HPP_INCLUDED
