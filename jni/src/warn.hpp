#ifndef WARN_HPP_INCLUDED
#define WARN_HPP_INCLUDED

#include "platform.hpp"     // for LOG

#define WARN(what, why)                             \
        LOG_W(what, why)

#define WARN_IF(problem, what, why)                 \
    if(problem)                                     \
        WARN(what, why)

#define WARN_RTN(what, why, rtn)                    \
    {                                               \
        WARN(what, why);                             \
        return(rtn);                                \
    }

#endif // WARN_HPP_INCLUDED
