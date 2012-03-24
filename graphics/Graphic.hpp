#ifndef GRAPHIC_HPP_INCLUDED
#define GRAPHIC_HPP_INCLUDED

#include "Texture.hpp"
#include "../math/Rect.hpp"

class Graphic
{
    /// ATTRIBUTES
    protected:
    Texture* texture;
    iRect frame; // the source area of

    /// METHODS
    public:
    // constructors, destructor
    Graphic();
    // main methods
    void init(Texture* init_texture, iRect init_frame);
    // accessors
    Texture* getTexture();
    iRect getFrame() const;
};

#endif // GRAPHIC_HPP_INCLUDED
