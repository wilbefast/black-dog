#include "Application.hpp"

#include "SDL_image.h" //IMG_Load


#include "global.hpp"   // needed for application defaults
#include "platform.hpp" // needed for LOG
#include "assert.hpp"   // needed for platform specific ASSERT macros
#include "file.hpp"     // needed for ASSET_PATH macro

#include "scenes/MainMenu.hpp"

/// CONSTRUCTOR & DESTRUCTOR (public)

Application::Application() :
initialised(false),
this_tick(0),
next_tick(0),
music(NULL)
{
    scene = new MainMenu();
}

Application::~Application()
{
    // Force clean if nessecary
    if(initialised)
        shutdown();
}

/// METHODS (public)

int Application::startup()
{
    // Already initialised!
    if(initialised)
    {
        LOG_W("Application startup", "Application already loaded!");
        return EXIT_SUCCESS;
    }

    // Set up SDL (create window and context for OpenGL)
    ASSERT(startSDL() == EXIT_SUCCESS, "Starting SDL");

    // Set up OpenGL/GLES "propre"
    ASSERT(startGL() == EXIT_SUCCESS, "Starting OpenGL/GLES");

    // Load the game objects
    ASSERT(scene->startup() == EXIT_SUCCESS, "Loading Scene");

    // Initialisation successful!
    initialised = true;
    return EXIT_SUCCESS;
}

// Perform a single application step, return exit flag if encountered
int Application::run()
{
    // Update current scene, switch to the next scene if
    // need be (in which case we break from the loop and restart).
    Scene* next = NULL;
    if(scene->update(&next) != Scene::NO_CHANGE)
        return setScene(next);

    // Redraw everything, game objects included
    draw();

    // Regulate the number of frames per second, pausing if nessecary
    wait();

    // Treat input events, check for exit conditions.
    int flag = treatEvents();
    if(flag == Application::BACK)
        // Attempt to return to previous Inteface - if impossible, return EXIT
        return setScene(scene->previous());
    else
        // Pass on either EXIT or CONTINUE code
        return flag;
}

int Application::shutdown()
{
    // Check if not initialised
    if(!initialised)
    {
        LOG_W("Application shutdown", "Application already unloaded!");
        return EXIT_SUCCESS;
    }

    // Close down the current scene
    scene->shutdown();
    delete scene;

    // Destory application display and control structures
    SDL_GL_MakeCurrent(NULL, NULL);
    SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

    // Stop and then free music
    Mix_HaltMusic();
	Mix_FreeMusic(music);

	// Shut down SDL
    Mix_CloseAudio();
	SDL_Quit();

	// Flag uninitialised and signal success
    initialised = false;
	return EXIT_SUCCESS;
}


/// SUB-METHODS (private)

int Application::startSDL()
{
    // Initialize SDL.
	ASSERT_SDL(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) >= 0,
		"Initialising SDL video and audio");

	// Open the window where we will draw. NB: Android will override the
	// specified height and width no matter what they are!
	window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, WINDOW_DEFAULT_W,
                           WINDOW_DEFAULT_H, WINDOW_FLAGS);
    ASSERT_SDL(window, "Opening SDL application window");

    // Since the window size can be overriden, check what it is actually
    SDL_GetWindowSize(window, &global::viewport.w, &global::viewport.h);

    // Open mixer
    //Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
    ASSERT_MIX(Mix_OpenAudio(SOUND_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
             MIX_DEFAULT_CHANNELS, SOUND_DEFAULT_CHUNK_SIZE) != -1,
            "Starting SDL Mixer");

    // Load and play music on loop (-1)
    //music = Mix_LoadMUS(ASSET_PATH("music.ogg"));
    //ASSERT_MIX(music, "Loading music file");
    //Mix_PlayMusic(music, -1);

    // Create the OpenGL context for the window we just opened
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    // Configure SDL/OpenGL interface
    SDL_GL_SetSwapInterval(1); // 1 = use vertical synchronisation (vsync)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_V_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_V_MINOR);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // No problems, return success code!
    return EXIT_SUCCESS;
}

int Application::startGL()
{
    glClearColor(0, 0, 0, 255);     // Black background by default
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, global::viewport.w, global::viewport.h);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, global::viewport.w, global::viewport.h, 0, -1, 1);
            //NB - I'm using a macro to change this to "glOrthof" for GLES1.1
    glMatrixMode(GL_MODELVIEW);

    // Always start with a clean slate ;)
    glLoadIdentity();

    // No problems, return success code!
    return EXIT_SUCCESS;
}

void Application::draw()
{
    // Clear the entire screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw any objects required by the current scene
    scene->draw();

    // Flip the buffers to update the screen
    SDL_GL_SwapWindow(window);
}

// Regulate the number of frames per second, pausing only if need be
void Application::wait()
{
    // Get the current time-stamp
    this_tick = SDL_GetTicks();

    // If it's not yet time for the next update, wait a will
	if (this_tick < next_tick )
		SDL_Delay(next_tick - this_tick);

    // Calculate when the next update should be
	next_tick = this_tick + (1000/MAX_FPS);
}

// deal with input messages, return BACK, EXIT or CONTINUE
int Application::treatEvents()
{
    // local variables
    static V2i cursor(0,0);
    static bool clicking(false);

    // static to avoid reallocating it ever time we run the function
    static SDL_Event event;


    // write each event to our static variable
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // exit if the window is closed (ex: pressing the cross)
            case SDL_QUIT:
                return Application::EXIT;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case KEY_BACK:
                        return Application::BACK;
                    case KEY_EXIT:
                        return Application::EXIT;
                    default:
                        break;
                }
                break;

            #if USE_TOUCH
            // touch events
            case SDL_FINGERDOWN:
                cursor = normaliseTouch(event.tfinger.touchId,
                                         V2i(event.tfinger.x, event.tfinger.y));
                clicking = true;
                break;

            case SDL_FINGERUP:
                clicking = false;
                break;

            case SDL_FINGERMOTION:
                cursor = normaliseTouch(event.tfinger.touchId,
                                        V2i(event.tfinger.x, event.tfinger.y));
                break;
            #endif  // USE_TOUCH

            #if USE_MOUSE
            // mouse events
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_RIGHT)
                    return Application::BACK;
                clicking = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                    clicking = false;
                break;

            case SDL_MOUSEMOTION:
                cursor = V2i(event.motion.x, event.motion.y);
                break;
            #endif  // USE_MOUSE

            default:
                break;
        }
    }

    // Update the scene with the new input
    scene->getState()->setCursor(cursor, clicking);

    // No exit events encountered, we can continue
    return Application::CONTINUE;
}

int Application::setScene(Scene* new_scene)
{
    // Check if there is a new scene to set
    if(!new_scene || (new_scene == scene))
        return Application::EXIT;

    // The new scene exists, but can it be started?
    if(new_scene->startup() != EXIT_SUCCESS)
    {
        // damage control: stay on the same scene
        new_scene->shutdown();
        return Application::CONTINUE;
    }


    // Out with the old...
    scene->shutdown();
    delete scene;

    // ... in with the new! That is, if possible
    scene = new_scene;

    // Success!
    return Application::CONTINUE;
}


/// CLASS NAMESPACE FUNCTIONS

V2i Application::normaliseTouch(SDL_TouchID device_id, V2i touch)
{
    // There's only 1 touch device: memorise it's resolution upon initial call
    static V2i device_resolution = V2i(SDL_GetTouch(device_id)->xres,
                                       SDL_GetTouch(device_id)->yres);

    // Normalise the touch position
    return touch * global::viewport.getSize() / device_resolution;
}
