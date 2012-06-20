#ifndef ANIMATEDELEMENT_HPP_INCLUDED
#define ANIMATEDELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../graphics/AnimationIncarnation.hpp"

class AnimatedElement : public ThingElement, public AnimationIncarnation
{
  /// METHODS
public:
  // contructors, destructors
  AnimatedElement(Thing* init_owner, V2f size = V2f(0.0f, 0.0f),
                                    V2f offset = V2f(0.0f, 0.0f),
                                    char flags = CENTER_X|CENTER_Y);
  ~AnimatedElement();

  // overrides
  int update(GameState* context);     // ThingElement
  void draw();                        // ThingElement

protected:
  void animEnd();                     // AnimationIncarnation
};

#endif // ANIMATEDELEMENT_HPP_INCLUDED
