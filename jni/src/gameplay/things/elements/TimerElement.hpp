#ifndef TIMERELEMENT_HPP_INCLUDED
#define TIMERELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"
#include "../../../resources/numerise.hpp"     // for str_id

class TimerElement : public ThingElement
{
    /// ATTRIBUTES
    private:
    str_id name;
    int remaining_time;


    /// METHODS
    public:
    TimerElement(Thing* _owner, const char* _name, int init_time = -1);
    bool ticking() const;
    void set(unsigned int time);
    void decrement();
};

#endif // TIMERELEMENT_HPP_INCLUDED
