#ifndef NUMERISE_HPP_INCLUDED
#define NUMERISE_HPP_INCLUDED

typedef unsigned int str_id;

/// MACRO HASH FUNCTION

#define INIT_HASH 5831         // the magic number, apparently.

#define REHASH(c, hash)                   \
    (((hash << 5) + hash) + c)

// I'd have liked to define a recursive macro but unfortunately this is
// impossible without an extensive such as "Boost".

#define NUMERISE_REC(str, i, hash)                                     \
    (*(str+i)) ? NUMERISE_REC(str, i+1, REHASH(str[i], hash)) : hash

#define NUMERISE(str) (NUMERISE_REC(str, 0, INIT_HASH))

/// INLINE HASH FUNCTION

// Inlines are the next best thing: hopefully GCC will be clever enough to
// optimise them.

str_id numerise(const char*);

#include "numerise.inl"

#endif // NUMERISE_HPP_INCLUDED
