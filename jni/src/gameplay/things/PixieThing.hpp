#ifndef PIXIETHING_HPP_INCLUDED
#define PIXIETHING_HPP_INCLUDED

#include "Thing.hpp"

#include "elements/AnimatedElement.hpp"
#include "elements/TimerElement.hpp"
#include "../../global.hpp" // for default window size

class PixieThing : public Thing
{
  /// CONSTANTS
private:
  static const int SIZE = 32, LEAD = 128, ORB_INTERVAL = 200, MAX_X = WINDOW_DEFAULT_W - 32;

  /// ATTRIBUTES
private:
  AnimatedElement graphic;
  TimerElement orb_timer;

  /// METHODS
public:
  // creation, destruction
  PixieThing(V2i _position);
  // overrides Thing
  int update(GameState*, float delta);
  void draw();
};

#endif // PIXIETHING_HPP_INCLUDED
