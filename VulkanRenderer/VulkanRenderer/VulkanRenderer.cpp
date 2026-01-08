#include"./VulkanRenderer.hpp"
#include <GLFW/glfw3.h>
#include"Renderer.hpp"
void VulkanRenderer::Init(const BackendInitInfo& info)
{
    GLFWwindow* window =
        static_cast<GLFWwindow*>(info.windowHandle);

    // init Vulkan instance, surface, swapchain...
}