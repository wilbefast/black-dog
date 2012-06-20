#ifndef PIXIETHING_HPP_INCLUDED
#define PIXIETHING_HPP_INCLUDED

#include "Thing.hpp"

#include "elements/AnimatedElement.hpp"

class PixieThing : public Thing
{
  /// CONSTANTS
private:
  static const int SIZE = 32, LEAD = 52;

  /// ATTRIBUTES
private:
  AnimatedElement graphic;

  /// METHODS
public:
  // creation, destruction
  PixieThing(V2i _position);
  // overrides Thing
  int update(GameState*);
  void draw();
};

#endif // PIXIETHING_HPP_INCLUDED
