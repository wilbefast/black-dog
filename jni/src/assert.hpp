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
