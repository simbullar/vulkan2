#ifndef INCLUDES_H
#define INCLUDES_H

#define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>

    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>

    #include <chrono>

    #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>
    #include <vulkan/vulkan.h>

    #include <iostream>

    #include <map>
    #include <optional>
    #include <set>
    #include <algorithm>

    #include <stdexcept>
    #include <cstdlib>
    #include <fstream>
const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    const int MAX_FRAMES_IN_FLIGHT = 2;

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};
struct UniformBufferObject {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};
const std::vector<Vertex> vertices = {
  {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
  {{0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
  {{0.5f, 0.5f},   {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
  {{-0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};
const std::vector<uint16_t> indices = {
  0, 1, 2, 2, 3, 0
};

#endif
