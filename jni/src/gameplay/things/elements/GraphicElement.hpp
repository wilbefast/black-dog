#ifndef GRAPHICELEMENT_HPP_INCLUDED
#define GRAPHICELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../graphics/GraphicIncarnation.hpp"

class GraphicElement : public ThingElement, public GraphicIncarnation
{
  /// METHODS
public:
  // contructors, destructors
  GraphicElement(Thing* init_owner, V2f _size = V2f(0.0f, 0.0f),
                                    V2f _offset = V2f(0.0f, 0.0f),
                                    char _flags = CENTER_X|CENTER_Y);
  ~GraphicElement();
  // overrides
  virtual int update(GameState* context);     // ThingElement
  virtual void draw();                        // ThingElement
};

#endif // GRAPHICELEMENT_HPP_INCLUDED
