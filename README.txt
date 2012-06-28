black-dog
================
A game by William J. Dyce (aka wilbefast).

This is a C++/SDL port of http://wilbefast.com/html5/black_dog for Android. I'm
away over the summer so I've decided to leave the source up for reference, in
case anybody needs a few pointers where Android NDK development is concerned.

PROJECT
---------------
The game logic and Code::Blocks project can be found in jni/src. This is my code
whereas the rest is, by and large, part of the SDL project. If you want to run
the game on Windows, Mac or Linux, this is the only part that will be of 
interest to you.

LIBRARIES
---------------
Download the following libraries and place them in the jni folder:
freetype  
mikmod  
SDL        
SDL_mixer  
SDL_ttf  
tremor
jpeg      
png
SDL_image
SDL_net

I'm actually getting a linker error with the newest version of SDL, and I don't
have time to fix it before I leave. The project compiles fine for the older
version I use, so I'm assuming it shouldn't be too difficult to resolve for the
newer version with the help of the SDL community.
If anybody figures this out before the end of Summer I'd be very grateful. If 
not I'll be back to take care of it myself ;)

Here's a link to the version I use, in case you're having trouble:
http://dl.dropbox.com/u/4522570/jni.tar.gz

COMPILING
---------------
There is a Code::Blocks project for compiling on Linux. Compiling for Android is
slightly more complicated.
Consult Google's documentation to find out how to install the Android SDK and
NDK for Eclipse. To compile run 'ndk-build' from the root of the project. If 
you've configured Eclipse correctly running the build should install and launch 
the application.

TIPS
---------------
- Remember to clean the project in Eclipse to make sure that the changes are 
taken into account.
- Make sure that the Android Debug Bridge (adb) is running with administrator 
rights: run 'sudo adb kill-server' then 'sudo adb start-server'.
