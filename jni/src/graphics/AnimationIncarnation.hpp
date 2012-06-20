#ifndef ANIMATIONINCARNATION_HPP_INCLUDED
#define ANIMATIONINCARNATION_HPP_INCLUDED

#include "GraphicIncarnation.hpp"
#include "Animation.hpp"

// Instance of an animation on the screen (with position, current frame, etc)

class AnimationIncarnation : public GraphicIncarnation
{
  /// ATTRIBUTES
protected:
  float frame_current;
  float frame_speed;

  /// METHODS
public:
  // contructors, destructors
  AnimationIncarnation(V2f size = V2f(0.0f, 0.0f),
                  V2f offset = V2f(0.0f, 0.0f),
                  char flags = CENTER_X|CENTER_Y);
  ~AnimationIncarnation();
  // accessors
  void setFrame(float new_frame);
  void setRandFrame();
  bool setSprite(Animation* new_sprite, float new_speed = 0);
  // modification
  void draw();

  /// SUBROUTINES
protected:
  void loopAnim();
  virtual void animEnd() { } // by default does nothing
};

#endif // ANIMATIONINCARNATION_HPP_INCLUDED
