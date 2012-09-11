/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Inline file: a special implementation that is included

#include "wjd_math.hpp"


using namespace std;

/// CONSTRUCTORS

// Point-rectangle
template <typename T>
inline Rect<T>::Rect() :
x(0), y(0), w(0), h(0)
{
}

// Basic constructor. Ex: Recti(3,3,6,6);
template <typename T>
inline Rect<T>::Rect(T xx, T yy, T ww, T hh) :
x(xx), y(yy), w(ww), h(hh)
{
}

// Copy constructor. Ex: Recti r2(r1);
template<typename T>
template<typename U>
inline Rect<T>::Rect(const Rect<U>& source) :
x(static_cast<T>(source.x)),
y(static_cast<T>(source.y)),
w(static_cast<T>(source.w)),
h(static_cast<T>(source.h))
{
}

// Construction from vector
template<typename T>
inline Rect<T>::Rect(const V2<T>& position, const V2<T>& size) :
x(position.x), y(position.y), w(size.x), h(size.y)
{
}

template<typename T>
inline Rect<T>::Rect(const V2<T>& size) :
x(0), y(0), w(size.x), h(size.y)
{
}

/// UTILITIES

// Static cast operator from Rect<T> to Rect<U>. Ex: (Rectu)rt;
template<typename T>
template<typename U>
inline Rect<T>::operator Rect<U>() const
{
    Rect<U> result;
    result.x = (U) x;
    result.y = (U) y;
    result.w = (U) w;
    result.h = (U) h;
    return result; // Return type is unspecified because it is fixed
}

// Evalulate a rectangle as a bool (false if invalid)
template<typename T>
inline Rect<T>::operator bool() const
{
    return ((w>0) && (h>0));
}

// Caste by affection from Rest<U> to Rect<T>. Ex: rt = ru;
template<typename T>
template <typename U>
inline Rect<T>& Rect<T>::operator= (const Rect<U> &source)
{
    x = (T)source.x;
    y = (T)source.y;
    w = (T)source.w;
    h = (T)source.h;
    return *this;
}

// Comparisons

template<typename T>
bool Rect<T>::operator==(const Rect<T>& other)
{
    return (x == other.x
            && y == other.y
            && w == other.w
            && h == other.h);
}


template<typename T>
bool Rect<T>::operator!=(const Rect<T>& other)
{
    return !((*this)==other);
}


/// TRANSFORM TO VECTOR

template<typename T>
inline V2<T> Rect<T>::getPosition()
{
    return V2<T>(x,y);
}

template<typename T>
inline V2<T> Rect<T>::getSize()
{
    return V2<T>(w,h);
}


/// TRANSLATION OF A RECTANGLE BY A VECTOR

template <typename T>
inline Rect<T>& Rect<T>::operator+=(V2<T> const&  move)
{
    this->x +=  move.x;
    this->y +=  move.y;

    return (*this);
}

template <typename T>
inline Rect<T> Rect<T>::operator+(V2<T> const&  move) const
{
    Rect<T> copy(*this);
    copy +=  move;
    return copy;
}

template <typename T>
inline Rect<T>& Rect<T>::operator-=(V2<T> const&  move)
{
    this->x -=  move.x;
    this->y -=  move.y;

    return (*this);
}

template <typename T>
inline Rect<T> Rect<T>::operator-(V2<T> const& move) const
{
    Rect<T> copy(*this);
    copy -=  move;
    return copy;
}


/// UNIFORM STRETCHING (BY SCALAR)

template <typename T>
inline Rect<T>& Rect<T>::operator*=(T k)
{
    this->w *= k;
    this->h *= k;

    return (*this);
}

template <typename T>
inline Rect<T> Rect<T>::operator*(T k) const
{
    Rect<T> copy(*this);
    copy *= k;
    return copy;
}

template <typename T>
inline Rect<T>& Rect<T>::operator/=(T k)
{
    this->w /= k;
    this->h /= k;

    return (*this);
}

template <typename T>
inline Rect<T> Rect<T>::operator/(T k) const
{
    Rect<T> copy(*this);
    copy /= k;
    return copy;
}


/// NON-UNIFORM STRETCHING (BY VECTOR)

template <typename T>
inline Rect<T>& Rect<T>::operator*=(V2<T> const& scale)
{
    this->w *= scale.x;
    this->h *= scale.y;
    return (*this);
}

template <typename T>
inline Rect<T> Rect<T>::operator*(V2<T> const& scale) const
{
    Rect<T> copy(*this);
    copy *= scale;
    return copy;
}

template <typename T>
inline Rect<T>& Rect<T>::operator/=(V2<T> const& scale)
{
    this->w /= scale.x;
    this->h /= scale.y;
    return (*this);
}

template <typename T>
inline Rect<T> Rect<T>::operator/(V2<T> const& scale) const
{
    Rect<T> copy(*this);
    copy /= scale;
    return copy;
}


/// ACCESSORS

template <typename T>
inline T Rect<T>::getRatio()
{
    return w/h;
}

template <typename T>
inline void Rect<T>::setRatio(T ratio)
{
    if(ratio > getRatio())
        h = w/ratio;
    else
        w = h*ratio;
}

template <typename T>
inline V2<T> Rect<T>::getPosition() const
{
    return V2<T>(x, y);
}

template <typename T>
inline void Rect<T>::setPosition(V2<T> const& new_position)
{
    x = new_position.x;
    y = new_position.y;
}

template <typename T>
inline V2<T> Rect<T>::getSize() const
{
    return V2<T>(w, h);
}

template <typename T>
inline void Rect<T>::setSize(V2<T> const& new_size)
{
    w = new_size.x;
    h = new_size.y;
}


/// CONTENTS

template <typename T>
bool Rect<T>::contains(T xx, T yy) const
{
    return (xx >= x)
        && (xx < x + w)
        && (yy >= y)
        && (yy < y + h);
}

template <typename T>
bool Rect<T>::contains(const V2<T>& position) const
{
    return this->contains(position.x, position.y);
}


// Intersection
template <typename T>
bool Rect<T>::doesInter(Rect<T> const& other) const
{
  V2d v1 = (other.getPosition()+other.getSize()) - this->getPosition();
  V2d v2 = (this->getPosition()+this->getSize()) - other.getPosition();
  return (dot(v1, v2) > 0);
}

template <typename T>
Rect<T> Rect<T>::getInter(Rect<T> const& other) const
{
  // Calculate the boundaries of the intersection
  T left   = MAX(x,      other.x);
  T top    = MAX(y,      other.y);
  T right  = MIN(x + w,  other.x + other.w);
  T bottom = MIN(y + h,  other.y + other.h);

  // If the intersection is invalid (negative lengths) return false
  if((left >= right ) || (top >= bottom))
      return Rect<T>(); //null rectangle: (0,0,0,0)
  else //non-negative lengths
    return Rect<T>(left, top, right - left, bottom - top);
}

/// FANCY STUFF

template <typename T>
void Rect<T>::centreWithin(Rect<T> const& container)
{
  if(w > container.w)
  {
    h *= container.w/w;
    w = container.w;
  }

  if(h > container.h)
  {
    w *= container.h/h;
    h = container.h;
  }

  x = container.x + container.w/2 - w/2;
  y = container.y + container.h/2 - h/2;
}

template <typename T>
inline void Rect<T>::stretch_centered(T k)
{
    (*this) += (getSize()*(1-k))/(T)2; // translate to keep centre
    (*this) *= k;                   // resize
}


/// OUTSTREAM OPERATOR

template <typename T>
inline void Rect<T>::print(ostream& stream) const
{
    stream << "(" << x << ", " << y << ", "
                  << w << ", " << h << ")";
}

template <typename T>
inline ostream& operator<<(std::ostream& stream, Rect<T> const& r)
{
    r.print(stream);
    return stream;
}
