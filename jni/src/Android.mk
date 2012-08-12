LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := 						        \
	$(LOCAL_PATH)/$(SDL_PATH)/include 		\
	$(LOCAL_PATH)/../SDL_image 				    \
	$(LOCAL_PATH)/../SDL_mixer

LOCAL_CFLAGS :=                         \
	-DSDL_NO_COMPAT

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.cpp \
  io/tinyxml/tinystr.cpp                                      \
  io/tinyxml/tinyxml.cpp                                      \
  io/tinyxml/tinyxml_dump.cpp                                 \
  io/tinyxml/tinyxmlerror.cpp                                 \
  io/tinyxml/tinyxmlparser.cpp                                \
  io/AudioManager.cpp						                              \
  io/GraphicsManager.cpp						                          \
  io/file.cpp						                                      \
  gameplay/things/elements/AnimatedElement.cpp		            \
  gameplay/things/elements/ColliderElement.cpp		            \
  gameplay/things/elements/GraphicElement.cpp		              \
  gameplay/things/elements/MovementElement.cpp		            \
  gameplay/things/elements/ResourceElement.cpp		            \
  gameplay/things/elements/ThingElement.cpp		                \
  gameplay/things/elements/TimerElement.cpp						        \
  gameplay/things/events/BoundaryEvent.cpp		                \
  gameplay/things/events/CollisionEvent.cpp		                \
  gameplay/things/events/ThingEvent.cpp                       \
  gameplay/things/AngelThing.cpp				                      \
  gameplay/things/DogThing.cpp				                        \
  gameplay/things/PixieThing.cpp				                      \
  gameplay/things/FallingThing.cpp				                    \
	gameplay/things/MinionThing.cpp				                      \
  gameplay/things/EffectThing.cpp				                      \
  gameplay/things/Thing.cpp				                            \
  gameplay/Tunnel.cpp					                                \
  gameplay/TunnelBG.cpp					                              \
  gameplay/TunnelFG.cpp					                              \
  graphics/Animation.cpp					                            \
  graphics/AnimationIncarnation.cpp					                  \
  graphics/Graphic.cpp					                              \
  graphics/GraphicIncarnation.cpp					                    \
  graphics/HeightMesh.cpp                                     \
  graphics/Mesh2D.cpp                                         \
  graphics/Texture.cpp					                              \
  graphics/draw.cpp					                                  \
  scenes/BlackDogState.cpp                                    \
  scenes/Button.cpp                                           \
  scenes/Game.cpp						                                  \
  scenes/GameState.cpp					                              \
  scenes/MainMenu.cpp					                                \
  scenes/Scene.cpp					                                  \
  scenes/SceneState.cpp					                              \
  Application.cpp                                             \
  global.cpp                                                  \
  jni_glue.cpp                                                \
  main.cpp


LOCAL_SHARED_LIBRARIES := SDL SDL_image SDL_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
