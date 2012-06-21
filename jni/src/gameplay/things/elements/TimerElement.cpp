#include "TimerElement.hpp"

TimerElement::TimerElement(Thing* _owner, const char* _name, int init_time) :
ThingElement(_owner),
name(numerise(_name)),
remaining_time(init_time < 0 ? 0 : init_time)
{
}

bool TimerElement::ticking() const
{
  return (remaining_time >= 0);
}

void TimerElement::set(unsigned int time)
{
  remaining_time = time;
}

void TimerElement::decrement(float delta)
{
  // decrement timer
  if(remaining_time > (int)delta)
    remaining_time -= (int)delta;
  else
  {
    owner->addEvent(new ThingEvent(name));
    remaining_time = -1;
  }
}
