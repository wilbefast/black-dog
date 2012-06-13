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
  // overrides Thing
  int update(GameState*);
};

#endif // DOGTHING_HPP_INCLUDED
