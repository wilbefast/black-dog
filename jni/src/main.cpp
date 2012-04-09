#include <stdlib.h>
#include <iostream>

#include "assert.hpp"
#include "BlackDogApplication.hpp"

#include "math/Rect.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    // Initialise random numbers
    srand(time(NULL));

    // Load up the application
    BlackDogApplication application;
    ASSERT_SDL(application.startup() == EXIT_SUCCESS, "Starting up application");

    // Run the application until an exit condition is encountered
    bool stop = false;
    do
        stop = application.run();
    while(!stop);

    // Shut down the application completely
	ASSERT_SDL(application.shutdown() == EXIT_SUCCESS, "Shutting down application");

    // Report a clean exit!
	return EXIT_SUCCESS;
}
