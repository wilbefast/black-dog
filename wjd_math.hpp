#ifndef WJD_MATH_HPP_INCLUDED
#define WJD_MATH_HPP_INCLUDED

#include <cmath>
#include <stdlib.h>

#define PI 3.14159265
#define RAD2DEG(r) (r*180/PI)
#define MAX(x,y) (x>y?x:y)
#define MIN(x,y) (x<y?x:y)
#define SIGN(x) (x>0?1:(x<0?-1:0))
#define ABS(x) ((x)*SIGN(x))
#define SQR(x) ((x)*(x))
#define RAND() (((double)rand())/RAND_MAX)
#define RAND_BETWEEN(x,y) (RAND()*ABS(x-y)+MIN(x,y))
#define RAND_SIGN() ((RAND()<0.5)?-1:1)

#endif // WJD_MATH_HPP_INCLUDED
