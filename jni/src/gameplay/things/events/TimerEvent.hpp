#ifndef TIMEREVENT_HPP_INCLUDED
#define TIMEREVENT_HPP_INCLUDED

class TimerEvent : public ThingEvent
{
  /// ATTRIBUTES
private:
  str_id timer_name;

  /// METHODS
public:
  // constructor, destructors
  TimerEvent(const char* init_type, const char* timer_name);
  // query
  str_id getName() const;
};

#endif // TIMEREVENT_HPP_INCLUDED
