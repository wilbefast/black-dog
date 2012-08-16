#ifndef EPILOGUETHING_HPP_INCLUDED
#define EPILOGUETHING_HPP_INCLUDED

#include "Thing.hpp"


#include "elements/AnimatedElement.hpp"

class EpilogueThing : public Thing
{
  /// ATTRIBUTES
private:
  AnimatedElement wraith, monk;
  unsigned int act;

  /// METHODS
public:
  // creation
  EpilogueThing(V2i _position);
  // overrides
  void draw();
  int update(GameState* context, float delta);
};

#endif // EPILOGUETHING_HPP_INCLUDED
