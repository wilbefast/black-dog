// Inline file: a special implementation that is included

#include "wjd_math.hpp"

using namespace std;

// Constructors

// Null vector
template <typename T>
inline V2<T>::V2() :
x(0), y(0)
{
}

// Basic constructor. Ex: V2i(3,3);
template <typename T>
inline V2<T>::V2(T xx, T yy) :
x(xx), y(yy)
{
}

// Copy constructor. Ex: V2i v2(v1);
template<typename T>
template<typename U>
inline V2<T>::V2(const V2<U>& source) :
x(static_cast<T>(source.x)),
y(static_cast<T>(source.y))
{
}

// Static cast operator from V2<T> to V2<U>. Ex: (V2u)vt;
template<typename T>
template<typename U>
inline V2<T>::operator V2<U>() const
{
    V2<U> result;
    result.x = (U) x;
    result.y = (U) y;
    return result; // Return type is unspecified because it is fixed
}

// Evalulate a vector as a bool (false if null-vector)
template<typename T>
inline V2<T>::operator bool() const
{
    return (x || y);
}

// Caste by affection from V2<U> to V2<T>. Ex: vt = vu;
template<typename T>
template <typename U>
inline V2<T>& V2<T>::operator= (const V2<U> &source)
{
    x = (T)source.x;
    y = (T)source.y;
    return *this;
}

// Vector addition and subtraction
template <typename T>
inline V2<T>& V2<T>::operator+=(V2 const& other)
{
    this->x += other.x;
    this->y += other.y;

    return (*this);
}

template <typename T>
inline V2<T> V2<T>::operator+(V2<T> const& other) const
{
    V2<T> copy(other);
    copy += (*this);
    return copy;
}

template <typename T>
inline V2<T>& V2<T>::operator-=(V2<T> const& other)
{
    this->x -= other.x;
    this->y -= other.y;

    return (*this);
}

template <typename T>
inline V2<T> V2<T>::operator-(V2<T> const& other) const
{
    V2<T> copy(*this);
    copy -= (other);
    return copy;
}

template <typename T>
inline V2<T> V2<T>::operator-() const
{
    return V2<T>(-x, -y);
}

// Multiplication/division by scalar
template <typename T>
inline V2<T>& V2<T>::operator*=(T k)
{
    this->x *= k;
    this->y *= k;

    return (*this);
}

template <typename T>
inline V2<T> V2<T>::operator*(T k) const
{
    V2<T> copy(*this);
    copy *= k;
    return copy;
}

template <typename T>
inline V2<T>& V2<T>::operator/=(T k)
{
    this->x /= k;
    this->y /= k;

    return (*this);
}

template <typename T>
inline V2<T> V2<T>::operator/(T k) const
{
    V2<T> copy(*this);
    copy /= k;
    return copy;
}

// Element-wise multiplication, division
template <typename T>
inline V2<T>& V2<T>::operator*=(V2 const& other)
{
    this->x *= other.x;
    this->y *= other.y;

    return (*this);
}

template <typename T>
inline V2<T> V2<T>::operator*(V2<T> const& other) const
{
    V2<T> copy(other);
    copy *= (*this);
    return copy;
}

template <typename T>
inline V2<T>& V2<T>::operator/=(V2<T> const& other)
{
    this->x /= other.x;
    this->y /= other.y;

    return (*this);
}

template <typename T>
inline V2<T> V2<T>::operator/(V2<T> const& other) const
{
    V2<T> copy(*this);
    copy /= (other);
    return copy;
}

// Create a vector of absolute values
template <typename T>
inline V2<T> V2<T>::abs() const
{
    return V2<T>(ABS(x), ABS(y));
}

// Create a "sign" vector, containing the signs of the x and y values
template <typename T>
inline V2<int> V2<T>::sign() const
{
    return V2<int>(SIGN(x), SIGN(y));
}

// Calculate the angle (degrees) corresponding to this Vector
template <typename T>
inline float V2<T>::getAngle() const
{
    return RAD2DEG(atan2(y, x));
}

// Calculate the norm (length) of the Vector
template <typename T>
inline float V2<T>::getNorm() const
{
    return sqrt(this->getNorm2());
}

template <typename T>
inline float V2<T>::getNorm2() const
{
    // This is less expensive since there is no sqrt to perform
    return x*x + y*y;
}

template <typename T>
inline void V2<T>::setMagnitude(float new_magnitude)
{
    (*this) *= (new_magnitude/getNorm());
}

// Outstream operator
template <typename T>
inline void V2<T>::print(ostream& stream) const
{
    stream << "(" << x << ", " << y << ")";
}

template <typename T>
inline ostream& operator<<(std::ostream& stream, V2<T> const& v)
{
    v.print(stream);
    return stream;
}

