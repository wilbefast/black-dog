#ifndef SYMETRICALMOVEMENTELEMENT_HPP_INCLUDED
#define SYMETRICALMOVEMENTELEMENT_HPP_INCLUDED

#include "MovementElement.hpp"

class SymetricalMovementElement : public MovementElement
{
  /// ATTRIBUTES
private:
  // pseudo-constant set upon creation of object
  float speed_max;
  float speed_min;
  float friction;

  /// METHODS
public:
  // creation, destruction
  SymetricalMovementElement(Thing* _owner, float speed_max, float friction = 1,
                            float speed_min = DEFAULT_SPEED_MIN);
  // main methods
  virtual int update(GameState* context, float delta);
  // modification
  virtual void setSpeed(V2f new_speed);
  void setSpeedMax(float _max_speed);
};

#endif // SYMETRICALMOVEMENTELEMENT_HPP_INCLUDED
