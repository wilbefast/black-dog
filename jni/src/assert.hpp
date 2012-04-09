#ifndef ASSERT_HPP_INCLUDED
#define ASSERT_HPP_INCLUDED

#include "SDL.h"        //needed for SDL_GetError()
#include "platform.hpp" //needed for LOG

#define ASSERT_AUX_RTN(assertion, what, why, rtn)       \
	if(!(assertion))                                    \
	{									                \
		LOG_E(what, why);	                            \
		return rtn;                                     \
    }                                                   \
    else                                                \
        LOG_I(what, "Okay")

#define ASSERT_AUX(assertion, what, why)                \
	ASSERT_AUX_RTN(assertion, what, why, EXIT_FAILURE)

#define ASSERT_RTN(assertion, what, rtn)                \
    ASSERT_AUX_RTN(assertion, what, "Failed", rtn)

#define ASSERT(assertion, what)                         \
    ASSERT_AUX(assertion, what, "Failed")

#define ASSERT_SDL(assertion, what)                     \
    ASSERT_AUX(assertion, what, SDL_GetError())

#define ASSERT_GL(assertion, what)                      \
    ASSERT_AUX(assertion, what, GL_GetError())

#define ASSERT_MIX(assertion, what)                     \
    ASSERT_AUX(assertion, what, Mix_GetError())



#endif // ASSERT_HPP_INCLUDED
