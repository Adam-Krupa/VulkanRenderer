#pragma once
#include "./Renderer.hpp"
#include<optional>
#include<vulkan/vulkan.hpp>
#include<GLFW/glfw3.h>
#include<filesystem>

struct Vertex
{
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static class VkVertexInputBindingDescription getBindingDescription();
    static std::array<class VkVertexInputAttributeDescription, 3> getAttributeDescription();
};
const int MAX_FRAMES_IN_FLIGHT = 2;
struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};
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
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif
static std::vector<char>readFile(const std::filesystem::path& path);
class VulkanRenderer : public RendererBackend
{
public:
    void Init(const BackendInitInfo& info) override;
    void Shutdown() override;

    void BeginFrame() override;
    void DrawIndexed(uint32_t indexCount) override;
    void EndFrame() override;
    void run();

public:

    bool framebufferResized = false;
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void drawFrame();

    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createTextureImage();
    void createCommandPool();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPools();
    void createDescriptorSets();
    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();
    void recreateSwapChain();
    void cleanupSwapChain();

    // --- Narzêdzia pomocnicze ---
    VkCommandBuffer beginSingleTimeCommands();
    void createTextureSampler();
    VkImageView createImageView(VkImage image, VkFormat format);
    void createTextureImageView();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void updateUniformBuffer(uint32_t currentFrame);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
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
private:
    GLFWwindow* window;

    BackendInitInfo windowInfo;
    uint32_t WIDTH;
    uint32_t HEIGHT;
    // Vulkan core
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkSwapchainKHR swapChain;
    VkImageView textureImageView;
    VkSampler textureSampler;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkDeviceMemory indexBufferMemory;
    VkDeviceMemory vertexBufferMemory;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    uint32_t currentFrame = 0;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;

    // --- Sync objects ---
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector < VkSemaphore> renderFinishedSemaphores;
    std::vector < VkFence> inFlightFences;
};