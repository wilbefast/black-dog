#include "TimerElement.hpp"

TimerElement::TimerElement(Thing* _owner, const char* _name, int init_time) :
ThingElement(_owner),
name(numerise(_name)),
remaining_time(init_time < 0 ? 0 : init_time)
{
}

bool TimerElement::ticking() const
{
  return remaining_time;
}

void TimerElement::set(unsigned int time)
{
  remaining_time = time;
}

void TimerElement::decrement()
{
  // decrement timer
  if(remaining_time)
    remaining_time--;
  else
    owner->addEvent(new ThingEvent(name));
}
