#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED

#ifdef __ANDROID__

    #include <android/log.h>    // for __android_log_print
	#include <GLES/gl.h>    	//OpenGL ES rather than OpenGL

	#define WINDOW_FLAGS WINDOW_DEFAULT_FLAGS|SDL_WINDOW_BORDERLESS

    #define USE_TOUCH 1
    #define USE_MOUSE 0
    #define KEY_EXIT SDLK_ESCAPE
	#define KEY_BACK 1073742094 // FIXME - use SDL macro: SDL_SCANCODE_AC_BACK?
	#define KEY_MENU 1073741942 // FIXME - use SDL macro: SDL_SCANCODE_AC_HOME?
	#define GL_V_MAJOR 2    	//GLES 2.0
	#define GL_V_MINOR 0
	#define glOrtho(a,b,c,d,e,f) glOrthof(a,b,c,d,e,f) // Renaming hack

    #define ASSET_PATH_PATH "" // use a bit of SDL RWops "magic" ;)
    #define BUFFER_XML 1

	#define LOG_I(what, why) \
		__android_log_print(ANDROID_LOG_INFO, "APP", "%s: %s", what, why)
	#define LOG_W(what, why) \
		__android_log_print(ANDROID_LOG_WARN, "APP", "%s: %s", what, why)
	#define LOG_E(what, why) \
		__android_log_print(ANDROID_LOG_ERROR, "APP", "%s: %s", what, why)

#else //LINUX, MAC, WINDOWS

    #ifdef WIN32
        #include <windows.h>    // must be included before GL
        #define GL_V_MAJOR 1    // OpenGL 1.1
        #define GL_V_MINOR 1
    #else
        #define GL_V_MAJOR 1    // OpenGL 1.5
        #define GL_V_MINOR 5
    #endif

	#include <stdio.h>  // for printf
	#include <GL/gl.h>  // for OpenGL rather than OpenGL ES

	#define WINDOW_FLAGS WINDOW_DEFAULT_FLAGS

    #define USE_TOUCH 0
    #define USE_MOUSE 1
	#define KEY_EXIT SDLK_ESCAPE
	#define KEY_MENU SDLK_ENTER
	#define KEY_BACK SDLK_SPACE

    #define ASSET_PATH_PATH "./assets/"
    #define BUFFER_XML 1

	#define LOG(level, what, why) \
		printf("%s - %s: %s\n", level, what, why)
	#define LOG_I(what, why) LOG("INFO", what, why)
	#define LOG_W(what, why) LOG("WARNING", what, why)
	#define LOG_E(what, why) LOG("ERROR", what, why)

#endif // __ANDROID__

#endif // PLATFORM_HPP_INCLUDED
