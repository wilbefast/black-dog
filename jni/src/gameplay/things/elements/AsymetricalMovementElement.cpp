#include "AsymetricalMovementElement.hpp"

using namespace std;

/// CREATION, DESTRUCTION

AsymetricalMovementElement::AsymetricalMovementElement(Thing* _owner,
                            V2f _speed_max, V2f _friction, V2f _speed_min) :
MovementElement(_owner),
speed_max(_speed_max),
speed_min(_speed_min),
friction(_friction)
{
}

/// MAIN METHODS

int AsymetricalMovementElement::update(GameState* context, float delta)
{
  // standard operations
  MovementElement::update(context, delta);

  // slow down
  if(friction.x)
    speed.x /= pow(friction.x, delta);
  if(friction.y)
    speed.y /= pow(friction.y, delta);

  // cap minimum speed, generate event if stopping
  if((abs(speed.x) < speed_min.x) || (abs(speed.y) < speed_min.y))
  {
    speed.x = speed.y = 0;
    owner->addEvent(new ThingEvent("stopped_moving"));
  }

  // all clear!
  return SceneState::CONTINUE;
}

/// MODIFICATION

void AsymetricalMovementElement::setSpeed(V2f new_speed)
{
  // default stuff
  MovementElement::setSpeed(new_speed);

  // terminal absolute velocity
  if(speed.x > speed_max.x)
    speed.x = speed_max.x;
  if(speed.y > speed_max.y)
    speed.y = speed_max.y;
}
