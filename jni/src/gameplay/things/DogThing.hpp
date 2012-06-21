#ifndef DOGTHING_HPP_INCLUDED
#define DOGTHING_HPP_INCLUDED

#include "elements/AnimatedElement.hpp"

class DogThing : public Thing
{
  /// CONSTANTS
private:
  static const int DEATH_THRESHOLD = 32;
  static const int DANGER_THRESHOLD = DEATH_THRESHOLD*4;
  static const int SAFETY_THRESHOLD = DANGER_THRESHOLD*1.1f;

  /// NESTING
private:
  enum State { OFFSCREEN, ARRIVE, IDLE, EAT, LEAVE };

  /// ATTRIBUTES
private:
  AnimatedElement graphic;
  State state;

  /// METHODS
public:
  // creation, destruction
  DogThing(V2i _position);
  // overrides Thing
  int update(GameState*, float delta);
  void draw();

  /// SUBROUTINES
private:
  void setState(State new_state);
  int treatEvent(ThingEvent* event);
};

#endif // DOGTHING_HPP_INCLUDED
