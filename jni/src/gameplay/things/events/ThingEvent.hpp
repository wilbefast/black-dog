#ifndef THINGEVENT_HPP_INCLUDED
#define THINGEVENT_HPP_INCLUDED

#include <iostream>     // for std::ostream
#include <list>

#include "../../../resources/numerise.hpp"

class ThingEvent;

typedef std::list<ThingEvent*> EventList;
typedef EventList::iterator EventIter;
typedef EventList::const_iterator ConstEventIter;

class ThingEvent
{
    /// ATTRIBUTES
    private:
    str_id type;   // hash

    /// METHODS
    public:
    // constructors, destructors
    ThingEvent(const char* init_type_name);
    // accessors
    str_id getType();
    bool isType(const char* type_name);

    // outstream operator
    void print(std::ostream& stream) const;
};

std::ostream& operator<<(std::ostream& stream, ThingEvent const& e);

#endif // THINGEVENT_HPP_INCLUDED
