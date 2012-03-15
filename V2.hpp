#ifndef V2_HPP_INCLUDED
#define V2_HPP_INCLUDED

#include <iostream>

#define ORIGIN(type) V2<type>(0,0)
#define SQUARE(type, size) V2<type>(SIZE,SIZE)

// Simple vector classes
template <typename T>
class V2
{
    /// ATTRIBUTES
    public:
        T x, y;

    /// METHODS
    public:
        // Constructors
        V2();
        V2(T x, T y);

        template <typename U>
        explicit V2(const V2<U>& source);

        // Cast operator: Conversion from one Vector type to another ;D
        template <typename U>
        operator V2<U>() const;

        // Conversion to a boolean
        operator bool() const;

        // Arithmetic operators
        template <typename U>
        V2& operator= (const V2<U>& source);
        // vector addition
        V2& operator+=(V2 const& other);
        V2 operator+(V2 const& other) const;
        V2& operator-=(V2 const& other);
        V2 operator-(V2 const& other) const;
        V2 operator-() const;   // unary minus or "additive inverse"
        // scaling
        V2& operator*=(T k);
        V2 operator*(T k) const;
        V2& operator/=(T k);
        V2 operator/(T k) const;
        // element-wise multiplication, division
        V2& operator*=(V2 const& other);
        V2 operator*(V2 const& other) const;
        V2& operator/=(V2 const& other);
        V2 operator/(V2 const& other) const;

        // accessors
        V2 abs() const;
        V2<int> sign() const;
        float getAngle() const;
        float getNorm() const;
        float getNorm2() const;
        void setMagnitude(float new_magnitude);

        // outstream operator
        void print(std::ostream& stream) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, V2<T> const& v);

typedef V2<int> V2i;
typedef V2<unsigned int> V2u;
typedef V2<float> V2f;
typedef V2<double> V2d;

// NB - "Inline" files are implementations that are included rather than
// compiled. They are especially useful for templates.
#include "V2.inl"

#endif // V2_HPP_INCLUDED

