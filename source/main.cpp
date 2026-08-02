#define STB_IMAGE_IMPLEMENTATION
#include "headers/m.h"

HelloTriangleApplication::HelloTriangleApplication()
    :     framebufferResized(false),
          currentFrame(0),
          deviceExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME}
    {};

void HelloTriangleApplication::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

  void HelloTriangleApplication::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
      drawFrame();
    }

    vkDeviceWaitIdle(device);
  }

  void HelloTriangleApplication::drawFrame() {
     vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

     uint32_t imageIndex;
     VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

     if (result == VK_ERROR_OUT_OF_DATE_KHR ) {
       recreateSwapChain();
       return;
     } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
       throw std::runtime_error("failed to acquired swap chain image!");
     }

     vkResetFences(device, 1, &inFlightFences[currentFrame]);

     vkResetCommandBuffer(commandBuffers[currentFrame], 0);
     recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

     updateUniformBuffer(currentFrame);

     VkSubmitInfo submitInfo{};
     submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

     VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
     VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
     submitInfo.waitSemaphoreCount = 1;
     submitInfo.pWaitSemaphores = waitSemaphores;
     submitInfo.pWaitDstStageMask = waitStages;
     submitInfo.commandBufferCount = 1;
     submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

     VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
     submitInfo.signalSemaphoreCount = 1;
     submitInfo.pSignalSemaphores = signalSemaphores;

     if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
       throw std::runtime_error("failed to submit draw command buffer!");
     }

     VkPresentInfoKHR presentInfo{};
     presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

     presentInfo.waitSemaphoreCount = 1;
     presentInfo.pWaitSemaphores = signalSemaphores;

     VkSwapchainKHR swapChains[] = {swapChain};
     presentInfo.swapchainCount = 1;
     presentInfo.pSwapchains = swapChains;
     presentInfo.pImageIndices = &imageIndex;

     result = vkQueuePresentKHR(presentQueue, &presentInfo);

     if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
       framebufferResized = false;
       recreateSwapChain();
     } else if (result != VK_SUCCESS) {
       throw std::runtime_error("failed to present swap chain image!");
     }

     currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
   }

  void HelloTriangleApplication::cleanup() {
    cleanupSwapChain();

    vkDestroySampler(device, textureSampler, nullptr);
    vkDestroyImageView(device, textureImageView, nullptr);

    vkDestroyImage(device, textureImage, nullptr);
    vkFreeMemory(device, textureImageMemory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
      vkDestroyBuffer(device, uniformBuffers[i], nullptr);
      vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(device, descriptorPool, nullptr);

    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);


    vkDestroyBuffer(device, indexBuffer, nullptr);
    vkFreeMemory(device, indexBufferMemory, nullptr);

    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);

    vkDestroyPipeline(device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

    vkDestroyRenderPass(device, renderPass, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
      vkDestroySemaphore(device,imageAvailableSemaphores[i], nullptr);
      vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
      vkDestroyFence(device, inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(device, commandPool, nullptr);

    vkDestroyDevice(device, nullptr);

    vkDestroySurfaceKHR(instance, surface, nullptr);

    vkDestroyInstance(instance,nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
  }

  VkCommandBuffer HelloTriangleApplication::beginSingleTimeCommands() {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
  }

  void HelloTriangleApplication::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    vkFreeCommandBuffers(device, commandPool,1, &commandBuffer);
  }


int main() {
  HelloTriangleApplication app;
  try {
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
