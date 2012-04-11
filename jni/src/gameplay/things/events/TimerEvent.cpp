#include "TimerEvent.hpp"

TimerEvent::ThingEvent(const char* init_type, const char* init_name)
ThingEvent(init_type),
name(numerise(init_name))
{
}

str_id TimerEvent::getName() const
{
  return name;
}
