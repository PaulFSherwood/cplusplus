#pragma once

#include "platform/SdlWindow.hpp"

#include <vulkan/vulkan.h>

#include <array>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string_view>
#include <vector>

namespace cube {

class VulkanRenderer final {
public:
    struct Vertex final {
        float position[3];
        float color[3];

        [[nodiscard]] static VkVertexInputBindingDescription bindingDescription() noexcept;
        [[nodiscard]] static std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions() noexcept;
    };

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT type,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userData);

    VulkanRenderer(SdlWindow& window, std::filesystem::path shaderDirectory, std::filesystem::path modelPath);
    ~VulkanRenderer();

    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer& operator=(const VulkanRenderer&) = delete;
    VulkanRenderer(VulkanRenderer&&) = delete;
    VulkanRenderer& operator=(VulkanRenderer&&) = delete;

    void drawFrame(float elapsedSeconds);
    void notifyFramebufferResized() noexcept { framebufferResized_ = true; }
    void waitIdle() const;

private:
    struct QueueFamilyIndices final {
        std::optional<std::uint32_t> graphicsFamily;
        std::optional<std::uint32_t> presentFamily;

        [[nodiscard]] bool complete() const noexcept {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapchainSupport final {
        VkSurfaceCapabilitiesKHR capabilities{};
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct Buffer final {
        VkBuffer handle{VK_NULL_HANDLE};
        VkDeviceMemory memory{VK_NULL_HANDLE};
    };

    struct Image final {
        VkImage handle{VK_NULL_HANDLE};
        VkDeviceMemory memory{VK_NULL_HANDLE};
        VkImageView view{VK_NULL_HANDLE};
    };

    struct UniformBufferObject final {
        alignas(16) float modelViewProjection[16]{};
    };

    static constexpr std::uint32_t maxFramesInFlight_ = 2;

    void loadModel();

    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapchainResources();
    void createSwapchain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createDepthResources();
    void createFramebuffers();
    void createCommandPool();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();

    void cleanupSwapchainResources();
    void recreateSwapchainResources();

    void recordCommandBuffer(VkCommandBuffer commandBuffer, std::uint32_t imageIndex, std::uint32_t frameIndex);
    void updateUniformBuffer(std::uint32_t frameIndex, float elapsedSeconds);

    [[nodiscard]] QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
    [[nodiscard]] SwapchainSupport querySwapchainSupport(VkPhysicalDevice device) const;
    [[nodiscard]] bool isDeviceSuitable(VkPhysicalDevice device) const;
    [[nodiscard]] bool checkDeviceExtensionSupport(VkPhysicalDevice device) const;
    [[nodiscard]] VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats) const;
    [[nodiscard]] VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& presentModes) const;
    [[nodiscard]] VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;
    [[nodiscard]] VkFormat findDepthFormat() const;
    [[nodiscard]] VkFormat findSupportedFormat(
        const std::vector<VkFormat>& candidates,
        VkImageTiling tiling,
        VkFormatFeatureFlags features) const;

    [[nodiscard]] std::vector<const char*> requiredInstanceExtensions() const;
    [[nodiscard]] bool validationLayersAvailable() const;
    [[nodiscard]] bool validationEnabled() const noexcept;
    [[nodiscard]] VkShaderModule createShaderModule(const std::filesystem::path& path) const;
    [[nodiscard]] std::uint32_t findMemoryType(std::uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
    [[nodiscard]] Buffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) const;
    [[nodiscard]] Image createImage(
        std::uint32_t width,
        std::uint32_t height,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        VkMemoryPropertyFlags properties) const;
    [[nodiscard]] VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) const;

    static void check(VkResult result, std::string_view operation);
    static std::vector<char> readBinaryFile(const std::filesystem::path& path);
    SdlWindow& window_;
    std::filesystem::path shaderDirectory_;
    std::filesystem::path modelPath_;

    std::vector<Vertex> vertices_;
    std::vector<std::uint32_t> indices_;

    VkInstance instance_{VK_NULL_HANDLE};
    VkDebugUtilsMessengerEXT debugMessenger_{VK_NULL_HANDLE};
    VkSurfaceKHR surface_{VK_NULL_HANDLE};
    VkPhysicalDevice physicalDevice_{VK_NULL_HANDLE};
    VkDevice device_{VK_NULL_HANDLE};
    VkQueue graphicsQueue_{VK_NULL_HANDLE};
    VkQueue presentQueue_{VK_NULL_HANDLE};

    VkSwapchainKHR swapchain_{VK_NULL_HANDLE};
    std::vector<VkImage> swapchainImages_;
    std::vector<VkImageView> swapchainImageViews_;
    VkFormat swapchainImageFormat_{VK_FORMAT_UNDEFINED};
    VkExtent2D swapchainExtent_{};

    VkRenderPass renderPass_{VK_NULL_HANDLE};
    VkDescriptorSetLayout descriptorSetLayout_{VK_NULL_HANDLE};
    VkPipelineLayout pipelineLayout_{VK_NULL_HANDLE};
    VkPipeline graphicsPipeline_{VK_NULL_HANDLE};
    Image depthImage_{};
    std::vector<VkFramebuffer> framebuffers_;

    VkCommandPool commandPool_{VK_NULL_HANDLE};
    std::vector<VkCommandBuffer> commandBuffers_;

    Buffer vertexBuffer_{};
    Buffer indexBuffer_{};
    std::array<Buffer, maxFramesInFlight_> uniformBuffers_{};
    std::array<void*, maxFramesInFlight_> mappedUniformMemory_{};

    VkDescriptorPool descriptorPool_{VK_NULL_HANDLE};
    std::array<VkDescriptorSet, maxFramesInFlight_> descriptorSets_{};

    std::array<VkSemaphore, maxFramesInFlight_> imageAvailableSemaphores_{};
    std::array<VkSemaphore, maxFramesInFlight_> renderFinishedSemaphores_{};
    std::array<VkFence, maxFramesInFlight_> inFlightFences_{};
    std::vector<VkFence> imagesInFlight_;
    std::uint32_t currentFrame_{0};
    bool framebufferResized_{false};
};

} // namespace cube
