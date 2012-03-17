LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := 						\
	$(LOCAL_PATH)/$(SDL_PATH)/include 		\
	$(LOCAL_PATH)/../SDL_image 				\
	$(LOCAL_PATH)/../SDL_mixer 
	
LOCAL_CFLAGS := \
	-DSDL_NO_COMPAT

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	main.cpp						\
	jni_glue.cpp						\
	file.cpp						\
	global.cpp						\
	Application.cpp						\
	AudioManager.cpp					\
	graphics/draw.cpp					\
	graphics/Texture.cpp					\
	graphics/Graphic.cpp					\
	graphics/Animation.cpp					\
	scenes/Game.cpp						\
	scenes/Scene.cpp					\
	scenes/MainMenu.cpp					\
	scenes/Button.cpp					\
	scenes/SceneState.cpp					\
	scenes/GameState.cpp					\
	gameplay/Tunnel.cpp					\
	gameplay/TunnelFG.cpp					\
	gameplay/TunnelBG.cpp					\
	gameplay/things/Thing.cpp				\
	gameplay/things/elements/ThingElement.cpp		\
	gameplay/things/elements/ColliderElement.cpp		\
	gameplay/things/elements/GraphicElement.cpp		\
	gameplay/things/elements/AnimatedElement.cpp		\
	gameplay/things/elements/MovementElement.cpp		\
	gameplay/things/elements/ResourceElement.cpp		\
	gameplay/things/events/CollisionEvent.cpp		\
	gameplay/things/events/BoundaryEvent.cpp		\
	gameplay/things/events/ThingEvent.cpp
					

LOCAL_SHARED_LIBRARIES := SDL SDL_image SDL_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
