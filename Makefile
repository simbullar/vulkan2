GLM_PATH = /opt/homebrew/opt/glm

CFLAGS = -std=c++17 -O2 /include -I$(GLM_PATH)/include -I$(VULKANINCLUDEPATH) -I$(STB_INCLUDE_PATH)

LDFLAGS = -L$(GLFW_PATH)/lib -L$(GLM_PATH)/lib -ldl -lpthread \
$(OBJC_LDFLAGS) -L$(VULKANLIBPATH) -Wl,-rpath,$(VULKANLIBPATH) -Wl,-rpath,$(VULKANFRAMEWORKPATH) \
-F$(VULKANFRAMEWORKPATH) -framework vulkan -ObjC

include local.mk # should look something like VULKANVERSION = 1.4.357.0

VULKANINCLUDEPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/include/
VULKANLIBPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/lib/
VULKANFRAMEWORKPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/Frameworks/
STB_INCLUDE_PATH = /Users/user/VulkanSDK/libraries/stb

OBJC_LDFLAGS = -ObjC -framework Foundation -framework AppKit -framework CoreGraphics -framework QuartzCore

CPP_SOURCES := $(wildcard source/*.cpp)
CPP_OBJS := $(patsubst source/%.cpp,build/obj/%.o,$(CPP_SOURCES))
OBJC_SOURCES := $(wildcard source/objc/*.m)
OBJC_OBJS := $(patsubst source/objc/%.m, build/obj/%.o, $(OBJC_SOURCES))
OBJS := $(CPP_OBJS) $(OBJC_OBJS)

.PHONY: all clear shaders

all: link

link: $(OBJS)
	g++ -o build/a.out build/obj/*.o $(LDFLAGS)

build/obj/%.o: source/%.cpp
	g++ $(CFLAGS) -c -o $@ $<

build/obj/%.o: source/objc/%.m
	gcc -c -o $@ $<

clear:
	-rm HelloTriangle
	-rm build/obj/*
shaders:
	./shaders/compile.sh
