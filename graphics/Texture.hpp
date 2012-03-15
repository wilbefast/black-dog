#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "../platform.hpp"     // Needed for GLuint
#include "../V2.hpp"           // Needed for V2i
#include "../Rect.hpp"         // Needed for iRect

class Texture
{
    /// ATTRIBUTES
    public:
    GLuint handle;
    private:
    iRect area; // size of the texture

    /// METHODS
    public:
    iRect getArea();
    int load(const char* filename);
    int unload();
    void draw(const fRect* source_pointer,
              const fRect* destination_pointer,
              float angle = 0.0);

};

#endif // TEXTURE_HPP_INCLUDED
