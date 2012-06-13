#ifndef DOGTHING_HPP_INCLUDED
#define DOGTHING_HPP_INCLUDED

#include "Thing.hpp"
#include "elements/AnimatedElement.hpp"

class DogThing : public Thing
{
  /// ATTRIBUTE
private:
  AnimatedElement graphic;

  /// METHODS
public:
  // creation, destruction
  DogThing(V2i _position);
  // overrides Thing
  int update(GameState*);
  void draw();
};

#endif // DOGTHING_HPP_INCLUDED
