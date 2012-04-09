#include "Button.hpp"

#include "../warn.hpp"

/// CONSTRUCTORS, DESTRUCTORS

Button::Button(const char* name, Texture init_texture, fRect init_destination,
               fRect init_source) :
tag(numerise(name)),
texture(init_texture),
destination(init_destination),
source_off(init_source),
source_on(init_source + V2u(init_source.w,0)),
pressed(false)
{
    correctAspect(init_source, init_destination);
}

Button::Button(str_id init_tag, Texture init_texture, fRect init_destination,
               fRect init_source) :
tag(init_tag),
texture(init_texture),
destination(init_destination),
source_off(init_source),
source_on(init_source + V2u(init_source.w,0)),
pressed(false)
{
    correctAspect(init_source, init_destination);
}

void Button::correctAspect(fRect src_area, fRect dest_area)
{
    destination.setRatio(src_area.getRatio());
    destination.centreWithin(dest_area);
}

Button::~Button()
{
}

/// EACH UPDATE

void Button::draw()
{
    if(pressed)
        texture.draw(&source_on, &destination);
    else
        texture.draw(&source_off, &destination);
}

/// ACCESSORS

bool Button::contains(V2f position) const
{
    return destination.contains(position);
}

bool Button::press(V2f position, bool clicking)
{
    // switch off button if not touching, otherwise turn or or off based on
    // position on touch.
    return (pressed = (clicking && contains(position)));
}

str_id Button::getTag() const
{
    return tag;
}
