#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>
#include <cstdint>
#include <limits> 
#include <algorithm>
#include <fstream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif
static std::vector<char>readFile(const std::filesystem::path& path);

// --- Funkcje pomocnicze Vulkan ---
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger
);

void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator
);

// --- Struktury pomocnicze ---
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete();
};
struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

// --- G³ówna klasa odpowiedzialna za setup Vulkan + okno ---
class SetupManager {
public:
    void run();

private:
    // Okno GLFW
    GLFWwindow* window;

    // Vulkan core
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    // --- Sync objects ---
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;

    // --- Funkcje inicjalizacyjne ---
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void drawFrame();

    // --- Vulkan setup ---
    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();

    // --- Narzêdzia pomocnicze ---
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkValidationLayerSupport();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapChainFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    std::vector<const char*> getRequiredExtensions();

    // --- Callback debugowania ---
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );
};
