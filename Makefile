GLFW_PATH = /opt/homebrew/opt/glfw
GLM_PATH = /opt/homebrew/opt/glm

CFLAGS = -std=c++17 -O2 -I$(GLFW_PATH)/include -I$(GLM_PATH)/include
LDFLAGS = -L$(GLFW_PATH)/lib -L$(GLM_PATH)/lib -lglfw -ldl -lpthread 
VULKANVERSION = YOUR_VULKAN_VERSION
VULKANINCLUDEPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/include/
VULKANLIBPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/lib/
VULKANFRAMEWORKPATH = /Users/user/VulkanSDK/$(VULKANVERSION)/macOS/Frameworks/
STB_INCLUDE_PATH = /Users/user/VulkanSDK/libraries/stb

.PHONY: shaders
HelloTriangle: main.cpp
	g++ $(CFLAGS) -o HelloTriangle main.cpp -F$(VULKANFRAMEWORKPATH) -framework vulkan -I$(VULKANINCLUDEPATH) -I$(STB_INCLUDE_PATH) -L$(VULKANLIBPATH) -Wl,-rpath,$(VULKANLIBPATH) -Wl,-rpath,$(VULKANFRAMEWORKPATH) $(LDFLAGS)
clear:
	rm HelloTriangle
shaders:
	./shaders/compile.sh
