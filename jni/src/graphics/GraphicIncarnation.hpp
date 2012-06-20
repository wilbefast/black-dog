#ifndef GRAPHICINCARNATION_HPP_INCLUDED
#define GRAPHICINCARNATION_HPP_INCLUDED

#include "Graphic.hpp"

// Instance of an graphic on the screen (with position, etc)

class GraphicIncarnation
{
  /// FLAGS
public:
  static const char CENTER_X = 0b00000001;
  static const char CENTER_Y = 0b00000010;

  /// ATTRIBUTES
protected:
  Graphic* sprite;
  fRect destination;
  V2f offset, size;
  float angle;
  char flags;

  /// METHODS
public:
  // contructors, destructors
  GraphicIncarnation(V2f _size = V2f(0.0f, 0.0f),
                    V2f _offset = V2f(0.0f, 0.0f),
                    char _flags = CENTER_X|CENTER_Y);
  ~GraphicIncarnation();
  // accessors
  void setAngle(float new_angle);
  bool setSprite(Graphic* new_sprite);
  // modificatio
  virtual void setPosition(V2f _position);
  virtual void draw();
};

#endif // GRAPHICINCARNATION_HPP_INCLUDED
