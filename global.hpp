#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include "Rect.hpp"

#define WINDOW_DEFAULT_FLAGS SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN
#define WINDOW_DEFAULT_W 640    // size used by Desktop version
#define WINDOW_DEFAULT_H 360
#define MAX_FPS 30
#define SOUND_DEFAULT_FREQUENCY 44100   // 48000 ?
#define SOUND_DEFAULT_CHUNK_SIZE 1024
#define APP_NAME "Black Dog"

namespace global
{
    extern iRect viewport;
};


#endif // GLOBAL_HPP_INCLUDED
