CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -ldl -lpthread
VULKANVERSION = 1.4.350.0
VULKANINCLUDEPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/include/
VULKANLIBPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/lib/
VULKANFRAMEWORKPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/Frameworks/
STB_INCLUDE_PATH = /Users/user/VulkanSDK/libraries/stb

HelloTriangle: main.cpp
	g++ $(CFLAGS) -o HelloTriangle main.cpp -F$(VULKANFRAMEWORKPATH) -framework vulkan -I$(VULKANINCLUDEPATH) -I$(STB_INCLUDE_PATH) -L$(VULKANLIBPATH) -Wl,-rpath,$(VULKANLIBPATH) -Wl,-rpath,$(VULKANFRAMEWORKPATH) $(LDFLAGS)
clear:
	rm HelloTriangle
shaders: shaders/source/*
	./shaders/compile.sh
