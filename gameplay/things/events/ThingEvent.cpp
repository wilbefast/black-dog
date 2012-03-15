#include "../../../numerise.hpp"
#include "ThingEvent.hpp"

using namespace std;


/// CONSTRUCTORS, DESTRUCTORS

ThingEvent::ThingEvent(const char* name) :
type(numerise(name))
{
}


/// ACCESSORS
str_id ThingEvent::getType()
{
    return type;
}

bool ThingEvent::isType(const char* name)
{
    return (type == numerise(name));
}


/// OUTSTREAM OPERATOR
void ThingEvent::print(ostream& stream) const
{
    stream << "ThingEvent " << type;
}

ostream& operator<<(std::ostream& stream, ThingEvent const& e)
{
    e.print(stream);
    return stream;
}
