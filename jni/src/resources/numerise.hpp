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
