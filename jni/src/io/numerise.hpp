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
#ifndef NUMERISE_HPP_INCLUDED
#define NUMERISE_HPP_INCLUDED

typedef unsigned int str_id;

/// MACRO HASH FUNCTION

#define INIT_HASH 5831         // the magic number, apparently.

#define REHASH(c, hash)                   \
    (((hash << 5) + hash) + c)

// I'd have liked to define a recursive macro but unfortunately this is
// impossible without an extension such as "Boost".

/*
#define NUMERISE_REC(str, i, hash)                                     \
    (*(str+i)) ? NUMERISE_REC(str, i+1, REHASH(str[i], hash)) : hash

#define NUMERISE(str) (NUMERISE_REC(str, 0, INIT_HASH))
*/

// not tested
/*
#define NUMERISE_REC7(str, hash)                                       \
  (*(str+7)) ? REHASH(str[7], hash) : hash
#define NUMERISE_REC6(str, hash)                                       \
  (*(str+6)) ? NUMERISE_REC7(str, REHASH(str[6], hash)) : hash
#define NUMERISE_REC5(str, hash)                                       \
  (*(str+5)) ? NUMERISE_REC6(str, REHASH(str[5], hash)) : hash
#define NUMERISE_REC4(str, hash)                                       \
  (*(str+4)) ? NUMERISE_REC5(str, REHASH(str[4], hash)) : hash
#define NUMERISE_REC3(str, hash)                                       \
  (*(str+3)) ? NUMERISE_REC4(str, REHASH(str[3], hash)) : hash
#define NUMERISE_REC2(str, hash)                                       \
  (*(str+2)) ? NUMERISE_REC3(str, REHASH(str[2], hash)) : hash
#define NUMERISE_REC1(str, hash)                                       \
  (*(str+1)) ? NUMERISE_REC2(str, REHASH(str[1], hash)) : hash
#define NUMERISE_REC0(str, hash)                                       \
  (*str) ? NUMERISE_REC1(str, REHASH(str[0], hash)) : hash

#define NUMERISE8(str) (NUMERISE_REC0(str, INIT_HASH))
*/

/// INLINE HASH FUNCTION

// Inlines are the next best thing: hopefully GCC will be clever enough to
// optimise them.

str_id numerise(const char*);

#include "numerise.inl"

#endif // NUMERISE_HPP_INCLUDED
