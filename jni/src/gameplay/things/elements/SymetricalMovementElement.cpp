#include "SymetricalMovementElement.hpp"

using namespace std;

/// CREATION, DESTRUCTION

SymetricalMovementElement::SymetricalMovementElement(Thing* _owner,
                  float _speed_max, float _friction, float _speed_min) :
MovementElement(_owner),
speed_max((_speed_max >= 0.0f) ? _speed_max : FLT_MAX),
speed_min(_speed_min),
friction(_friction)
{
}

/// MAIN METHODS

int SymetricalMovementElement::update(GameState* context, float delta)
{
  // standard operations
  MovementElement::update(context, delta);

  // slow down
  if(friction)
    speed /= pow(friction, delta);

  // cap minimum speed, generate event if stopping
  if(speed && (abs(speed.x) < speed_min) && (abs(speed.y) < speed_min))
  {
    speed.x = speed.y = 0;
    owner->addEvent(new ThingEvent("stopped_moving"));
  }

  // all clear!
  return SceneState::CONTINUE;
}

/// MODIFICATION

void SymetricalMovementElement::setSpeed(V2f new_speed)
{
  // default stuff
  MovementElement::setSpeed(new_speed);

  // terminal absolute velocity
  if(speed_scalar > speed_max)
    speed = (speed/speed_scalar)*speed_max; // normalise and remultiply
}

void SymetricalMovementElement::setSpeedMax(float _speed_max)
{
  speed_max = _speed_max;
}

