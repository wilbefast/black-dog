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
	main.cpp								\
	jni_glue.cpp							\
	file.cpp								\
	global.cpp								\
	Application.cpp							\
	ResourceManager.cpp						\
	graphics/draw.cpp						\
	graphics/Texture.cpp					\
	graphics/Graphic.cpp					\
	graphics/Animation.cpp					\
	interfaces/Game.cpp						\
	interfaces/Interface.cpp				\
	interfaces/LevelSelection.cpp			\
	interfaces/LogoScreen.cpp				\
	interfaces/MainMenu.cpp					\
	interfaces/WorldSelection.cpp			\
	interfaces/Button.cpp					\
	interfaces/InterfaceState.cpp			\
	interfaces/GameState.cpp				\
	tinyxml/tinystr.cpp						\
	tinyxml/tinyxml.cpp						\
	tinyxml/tinyxmlerror.cpp				\
	tinyxml/tinyxmlparser.cpp				\
	things/Thing.cpp						\
	things/SnackThing.cpp					\
	things/HeroThing.cpp					\
	things/MinibossThing.cpp					\
	things/BlockThing.cpp					\
	things/elements/ThingElement.cpp		\
	things/elements/ColliderElement.cpp		\
	things/elements/GraphicElement.cpp		\
	things/elements/AnimatedElement.cpp		\
	things/elements/MovementElement.cpp		\
	things/elements/ResourceElement.cpp		\
	things/events/CollisionEvent.cpp		\
	things/events/BoundaryEvent.cpp			\
	things/events/ThingEvent.cpp
					

LOCAL_SHARED_LIBRARIES := SDL SDL_image SDL_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
