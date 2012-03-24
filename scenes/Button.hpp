#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "../graphics/Texture.hpp"
#include "../math/Rect.hpp"
#include "../resources/numerise.hpp"

class Button;

#include <list>

typedef std::list<Button*> ButtonSet;
typedef ButtonSet::iterator ButtonIter;

class Button
{
    /// ATTRIBUTES
    private:
    str_id tag;
    Texture texture;
    fRect destination;
    fRect source_off;
    fRect source_on;
    bool pressed;

    /// METHODS
    public:
    // constructors, destructors
    Button(const char* name, Texture init_texture, fRect init_destination,
               fRect init_source);
    Button(str_id init_tag, Texture init_texture, fRect init_destination,
           fRect init_source);
    ~Button();
    void correctAspect(fRect init_src, fRect init_dest);
    // each frame
    void draw();
    // accessors
    str_id getTag() const;
    bool contains(V2f position) const;
    bool press(V2f position, bool clicking);
};

#endif // BUTTON_HPP_INCLUDED
