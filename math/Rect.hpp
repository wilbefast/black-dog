#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED

#include <iostream>

#include "V2.hpp"

// Simple rectangle classes
template <typename T>
class Rect
{
    /// ATTRIBUTES
    public:
        T x, y, w, h;

    /// METHODS
    public:
        /// Constructors
        // basic
        Rect();
        Rect(T x, T y, T w, T h);
        // copy
        template <typename U>
        explicit Rect(const Rect<U>& source);
        // vector
        Rect(const V2<T>& position, const V2<T>& size);
        Rect(const V2<T>& size);

        // Cast operator: Conversion from one Rect type to another ;D
        template <typename U>
        operator Rect<U>() const;

        // Conversion to a boolean
        operator bool() const;

        // Comparisons
        bool operator==(const Rect<T>& other);
        bool operator!=(const Rect<T>& other);

        // Affectation-cast
        template <typename U>
        Rect& operator= (const Rect<U>& source);

        // Transform to vectors
        V2<T> getPosition();
        V2<T> getSize();

        // Translate the rectangle (by a vector)
        Rect& operator+=(V2<T> const& move);
        Rect operator+(V2<T> const& move) const;
        Rect& operator-=(V2<T> const& move);
        Rect operator-(V2<T> const& move) const;

        // Remove sections of the rectangle
        Rect& operator-=(Rect<T> const& other);
        Rect operator-(Rect<T> const& other) const;

        // Uniformly grow/shrink the rectangle (by a scalar)
        Rect& operator*=(T k);
        Rect operator*(T k) const;
        Rect& operator/=(T k);
        Rect operator/(T k) const;

        // Un-uniformly grow/shrink the rectangle (by a vector)
        Rect& operator*=(V2<T> const& scale);
        Rect operator*(V2<T> const& scale) const;
        Rect& operator/=(V2<T> const& scale);
        Rect operator/(V2<T> const& scale) const;

        // Accessors
        T getRatio();
        void setRatio(T);
        V2<T> getPosition() const;
        void setPosition(V2<T> const& new_position);
        V2<T> getSize() const;
        void setSize(V2<T> const& new_size);

        // Fancy stuff
        void centreWithin(Rect<T> const& container);
        void stretch_centered(T k);

        // Contents and intersection checks
        bool contains(const T x, const T y) const;
        bool contains(V2<T> const& position) const;
        bool doesInter(Rect<T> const& other) const;
        Rect<T> getInter(Rect<T> const& other) const;

        // Outstream operator
        void print(std::ostream& stream) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, Rect<T> const& r);

typedef Rect<int> iRect;
typedef Rect<unsigned int> uRect;
typedef Rect<float> fRect;
typedef Rect<double> dRect;

// NB - "Inline" files are implementations that are included rather than
// compiled. They are especially useful for templates.
#include "Rect.inl"

#endif // RECT_HPP_INCLUDED
