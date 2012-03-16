#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED

#include "../V2.hpp"

#define CIRCLE_N_SEGMENTS 12

namespace draw
{
    /// NESTING
    class Colour
    {
        public:
        // attributes
        float r, g, b, a;
        // methods
        Colour(float _r = 1, float _g = 1, float _b = 1, float _a = 1) :
        r(_r), g(_g), b(_b), a(_a) { }
    };

    /// FUNCTIONS
    void line(V2f start, V2f end, Colour c = Colour(), float thickness = 1.0f);
    void line_loop(V2f points[], unsigned int n_pts, Colour c = Colour(),
                                                  float thickness = 1.0f);
    void height_line(float height[], unsigned int n_pts, float x_spacing,
                    V2f base = V2f(0.0f, 0.0f), unsigned int start_i = 0,
                    Colour c = Colour(), float thickness = 1.0f);
    void height_fill(float height[], unsigned int n_pts, float x_spacing,
                V2f base = V2f(0.0f, 0.0f), unsigned int start_i = 0,
                Colour c = Colour());
    void circle(V2f position, double radius, Colour c = Colour(),
                     bool fill = false);
};

#endif // GRAPHICS_HPP_INCLUDED
