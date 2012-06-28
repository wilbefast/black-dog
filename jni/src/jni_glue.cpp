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
#ifdef __ANDROID__

#include <jni.h>

#include "SDL_config.h"
#include "SDL_stdinc.h"

// Wraps the default SDL names to allow for new packages with unique identifiers

// Written by Gabriel Jacobo: http://mdqinc.com/blog/

//static float fLastAccelerometer[3];
extern "C"
{
    void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(JNIEnv* env,
                                                               jclass cls);
    void Java_org_libsdl_app_SDLActivity_onNativeResize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height, jint format);
    void Java_org_libsdl_app_SDLActivity_onNativeKeyDown(
                                    JNIEnv* env, jclass jcls, jint keycode);
    void Java_org_libsdl_app_SDLActivity_onNativeKeyUp(
                                    JNIEnv* env, jclass jcls, jint keycode);
    void Java_org_libsdl_app_SDLActivity_onNativeTouch(
                                    JNIEnv* env, jclass jcls,
                                    jint touch_device_id_in, jint pointer_finger_id_in,
                                    jint action, jfloat x, jfloat y, jfloat p);
    void Java_org_libsdl_app_SDLActivity_onNativeAccel(
                                    JNIEnv* env, jclass jcls,
                                    jfloat x, jfloat y, jfloat z);
    void Java_org_libsdl_app_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls);
    void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls);
    void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj);
};

// Resize
extern "C" void Java_com_wilbefast_blackdog_SDLActivity_onNativeResize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height, jint format)
{
    Java_org_libsdl_app_SDLActivity_onNativeResize(env, jcls, width, height, format);
}

// Keydown
extern "C" void Java_com_wilbefast_blackdog_SDLActivity_onNativeKeyDown(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Java_org_libsdl_app_SDLActivity_onNativeKeyDown(env, jcls, keycode);
}

// Keyup
extern "C" void Java_com_wilbefast_blackdog_SDLActivity_onNativeKeyUp(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Java_org_libsdl_app_SDLActivity_onNativeKeyUp(env, jcls, keycode);
}

// Touch
extern "C" void Java_com_wilbefast_blackdog_SDLActivity_onNativeTouch(
                                    JNIEnv* env, jclass jcls,
                                    jint touch_device_id_in, jint pointer_finger_id_in,
                                    jint action, jfloat x, jfloat y, jfloat p)
{
    Java_org_libsdl_app_SDLActivity_onNativeTouch(env, jcls, touch_device_id_in, pointer_finger_id_in, action, x, y, p);
}

// Accelerometer
extern "C" void Java_com_wilbefast_blackdog_SDLActivity_onNativeAccel(
                                    JNIEnv* env, jclass jcls,
                                    jfloat x, jfloat y, jfloat z)
{
     Java_org_libsdl_app_SDLActivity_onNativeAccel(env, jcls, x, y, z);
}

// Quit
extern "C" void Java_com_wilbefast_blackdog_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls)
{
    Java_org_libsdl_app_SDLActivity_nativeQuit(env, cls);
}

extern "C" void Java_com_wilbefast_blackdog_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls)
{
    Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(env, cls);
}

extern "C" void Java_com_wilbefast_blackdog_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj) {
    Java_org_libsdl_app_SDLActivity_nativeInit(env, cls, obj);
}

#endif // ifdef __ANDROID__
