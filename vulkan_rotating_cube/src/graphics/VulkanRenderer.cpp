#include "graphics/VulkanRenderer.hpp"

#include "math/Mat4.hpp"

#include <SDL2/SDL_vulkan.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>

namespace cube {
namespace {

constexpr std::array<const char*, 1> validationLayers{
    "VK_LAYER_KHRONOS_validation"};

constexpr std::array<const char*, 1> deviceExtensions{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

[[nodiscard]] VkDebugUtilsMessengerCreateInfoEXT makeDebugMessengerCreateInfo() noexcept {
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = VulkanRenderer::debugCallback;
    return createInfo;
}

} // namespace

VkVertexInputBindingDescription VulkanRenderer::Vertex::bindingDescription() noexcept {
    VkVertexInputBindingDescription description{};
    description.binding = 0;
    description.stride = sizeof(Vertex);
    description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return description;
}

std::array<VkVertexInputAttributeDescription, 2> VulkanRenderer::Vertex::attributeDescriptions() noexcept {
    std::array<VkVertexInputAttributeDescription, 2> descriptions{};

    descriptions[0].binding = 0;
    descriptions[0].location = 0;
    descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    descriptions[0].offset = offsetof(Vertex, position);

    descriptions[1].binding = 0;
    descriptions[1].location = 1;
    descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    descriptions[1].offset = offsetof(Vertex, color);

    return descriptions;
}

VulkanRenderer::VulkanRenderer(
    SdlWindow& window,
    std::filesystem::path shaderDirectory,
    std::filesystem::path modelPath)
    : window_{window},
      shaderDirectory_{std::move(shaderDirectory)},
      modelPath_{std::move(modelPath)} {
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createDescriptorSetLayout();
    createCommandPool();
    createSwapchainResources();
    loadModel();
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSets();
    createCommandBuffers();
    createSyncObjects();
}

VulkanRenderer::~VulkanRenderer() {
    if (device_ != VK_NULL_HANDLE) {
        (void)vkDeviceWaitIdle(device_);
    }

    cleanupSwapchainResources();

    if (descriptorPool_ != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(device_, descriptorPool_, nullptr);
    }

    for (std::size_t i = 0; i < uniformBuffers_.size(); ++i) {
        if (mappedUniformMemory_[i] != nullptr) {
            vkUnmapMemory(device_, uniformBuffers_[i].memory);
        }
        if (uniformBuffers_[i].handle != VK_NULL_HANDLE) {
            vkDestroyBuffer(device_, uniformBuffers_[i].handle, nullptr);
        }
        if (uniformBuffers_[i].memory != VK_NULL_HANDLE) {
            vkFreeMemory(device_, uniformBuffers_[i].memory, nullptr);
        }
    }

    if (indexBuffer_.handle != VK_NULL_HANDLE) {
        vkDestroyBuffer(device_, indexBuffer_.handle, nullptr);
    }
    if (indexBuffer_.memory != VK_NULL_HANDLE) {
        vkFreeMemory(device_, indexBuffer_.memory, nullptr);
    }

    if (vertexBuffer_.handle != VK_NULL_HANDLE) {
        vkDestroyBuffer(device_, vertexBuffer_.handle, nullptr);
    }
    if (vertexBuffer_.memory != VK_NULL_HANDLE) {
        vkFreeMemory(device_, vertexBuffer_.memory, nullptr);
    }

    for (const auto fence : inFlightFences_) {
        if (fence != VK_NULL_HANDLE) {
            vkDestroyFence(device_, fence, nullptr);
        }
    }
    for (const auto semaphore : renderFinishedSemaphores_) {
        if (semaphore != VK_NULL_HANDLE) {
            vkDestroySemaphore(device_, semaphore, nullptr);
        }
    }
    for (const auto semaphore : imageAvailableSemaphores_) {
        if (semaphore != VK_NULL_HANDLE) {
            vkDestroySemaphore(device_, semaphore, nullptr);
        }
    }

    if (commandPool_ != VK_NULL_HANDLE) {
        vkDestroyCommandPool(device_, commandPool_, nullptr);
    }

    if (pipelineLayout_ != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(device_, pipelineLayout_, nullptr);
    }

    if (descriptorSetLayout_ != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(device_, descriptorSetLayout_, nullptr);
    }

    if (device_ != VK_NULL_HANDLE) {
        vkDestroyDevice(device_, nullptr);
    }

    if (surface_ != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance_, surface_, nullptr);
    }

    if (debugMessenger_ != VK_NULL_HANDLE) {
        const auto destroyFn = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance_, "vkDestroyDebugUtilsMessengerEXT"));
        if (destroyFn != nullptr) {
            destroyFn(instance_, debugMessenger_, nullptr);
        }
    }

    if (instance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(instance_, nullptr);
    }
}

void VulkanRenderer::drawFrame(float elapsedSeconds) {
    const VkExtent2D drawable = window_.drawableExtent();
    if (drawable.width == 0 || drawable.height == 0) {
        return;
    }

    vkWaitForFences(device_, 1, &inFlightFences_[currentFrame_], VK_TRUE, std::numeric_limits<std::uint64_t>::max());

    std::uint32_t imageIndex = 0;
    const VkResult acquireResult = vkAcquireNextImageKHR(
        device_,
        swapchain_,
        std::numeric_limits<std::uint64_t>::max(),
        imageAvailableSemaphores_[currentFrame_],
        VK_NULL_HANDLE,
        &imageIndex);

    if (acquireResult == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapchainResources();
        return;
    }
    if (acquireResult != VK_SUCCESS && acquireResult != VK_SUBOPTIMAL_KHR) {
        check(acquireResult, "vkAcquireNextImageKHR");
    }

    if (imagesInFlight_[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(device_, 1, &imagesInFlight_[imageIndex], VK_TRUE, std::numeric_limits<std::uint64_t>::max());
    }
    imagesInFlight_[imageIndex] = inFlightFences_[currentFrame_];

    updateUniformBuffer(currentFrame_, elapsedSeconds);

    vkResetFences(device_, 1, &inFlightFences_[currentFrame_]);
    check(vkResetCommandBuffer(commandBuffers_[currentFrame_], 0), "vkResetCommandBuffer");
    recordCommandBuffer(commandBuffers_[currentFrame_], imageIndex, currentFrame_);

    const VkSemaphore waitSemaphores[] = {imageAvailableSemaphores_[currentFrame_]};
    const VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    const VkSemaphore signalSemaphores[] = {renderFinishedSemaphores_[currentFrame_]};

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers_[currentFrame_];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    check(vkQueueSubmit(graphicsQueue_, 1, &submitInfo, inFlightFences_[currentFrame_]), "vkQueueSubmit");

    const VkSwapchainKHR swapchains[] = {swapchain_};
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapchains;
    presentInfo.pImageIndices = &imageIndex;

    const VkResult presentResult = vkQueuePresentKHR(presentQueue_, &presentInfo);
    if (presentResult == VK_ERROR_OUT_OF_DATE_KHR || presentResult == VK_SUBOPTIMAL_KHR || framebufferResized_) {
        framebufferResized_ = false;
        recreateSwapchainResources();
    } else {
        check(presentResult, "vkQueuePresentKHR");
    }

    currentFrame_ = (currentFrame_ + 1U) % maxFramesInFlight_;
}

void VulkanRenderer::waitIdle() const {
    if (device_ != VK_NULL_HANDLE) {
        check(vkDeviceWaitIdle(device_), "vkDeviceWaitIdle");
    }
}

void VulkanRenderer::createInstance() {
    if (validationEnabled() && !validationLayersAvailable()) {
        throw std::runtime_error{"Validation layers requested, but VK_LAYER_KHRONOS_validation is not available."};
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Rotating Cube";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    const auto extensions = requiredInstanceExtensions();
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<std::uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (validationEnabled()) {
        createInfo.enabledLayerCount = static_cast<std::uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
        debugCreateInfo = makeDebugMessengerCreateInfo();
        createInfo.pNext = &debugCreateInfo;
    }

    check(vkCreateInstance(&createInfo, nullptr, &instance_), "vkCreateInstance");
}

void VulkanRenderer::setupDebugMessenger() {
    if (!validationEnabled()) {
        return;
    }

    const auto createFn = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance_, "vkCreateDebugUtilsMessengerEXT"));
    if (createFn == nullptr) {
        throw std::runtime_error{"vkCreateDebugUtilsMessengerEXT is unavailable."};
    }

    auto createInfo = makeDebugMessengerCreateInfo();
    check(createFn(instance_, &createInfo, nullptr, &debugMessenger_), "vkCreateDebugUtilsMessengerEXT");
}

void VulkanRenderer::createSurface() {
    if (SDL_Vulkan_CreateSurface(window_.nativeHandle(), instance_, &surface_) != SDL_TRUE) {
        throw std::runtime_error{"SDL_Vulkan_CreateSurface failed: " + std::string{SDL_GetError()}};
    }
}

void VulkanRenderer::pickPhysicalDevice() {
    std::uint32_t deviceCount = 0;
    check(vkEnumeratePhysicalDevices(instance_, &deviceCount, nullptr), "vkEnumeratePhysicalDevices count");
    if (deviceCount == 0) {
        throw std::runtime_error{"No Vulkan-capable physical devices found."};
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    check(vkEnumeratePhysicalDevices(instance_, &deviceCount, devices.data()), "vkEnumeratePhysicalDevices data");

    for (const auto device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice_ = device;
            return;
        }
    }

    throw std::runtime_error{"No suitable Vulkan physical device found."};
}

void VulkanRenderer::createLogicalDevice() {
    const QueueFamilyIndices indices = findQueueFamilies(physicalDevice_);
    const std::set<std::uint32_t> uniqueFamilies{
        indices.graphicsFamily.value(),
        indices.presentFamily.value()};

    const float queuePriority = 1.0F;
    std::vector<VkDeviceQueueCreateInfo> queueInfos;
    for (const std::uint32_t family : uniqueFamilies) {
        VkDeviceQueueCreateInfo queueInfo{};
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueFamilyIndex = family;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &queuePriority;
        queueInfos.push_back(queueInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_FALSE;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<std::uint32_t>(queueInfos.size());
    createInfo.pQueueCreateInfos = queueInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<std::uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (validationEnabled()) {
        createInfo.enabledLayerCount = static_cast<std::uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }

    check(vkCreateDevice(physicalDevice_, &createInfo, nullptr, &device_), "vkCreateDevice");
    vkGetDeviceQueue(device_, indices.graphicsFamily.value(), 0, &graphicsQueue_);
    vkGetDeviceQueue(device_, indices.presentFamily.value(), 0, &presentQueue_);
}

void VulkanRenderer::createSwapchainResources() {
    createSwapchain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createDepthResources();
    createFramebuffers();
    imagesInFlight_.assign(swapchainImages_.size(), VK_NULL_HANDLE);
}

void VulkanRenderer::createSwapchain() {
    const SwapchainSupport support = querySwapchainSupport(physicalDevice_);
    const VkSurfaceFormatKHR surfaceFormat = chooseSurfaceFormat(support.formats);
    const VkPresentModeKHR presentMode = choosePresentMode(support.presentModes);
    const VkExtent2D extent = chooseSwapExtent(support.capabilities);

    std::uint32_t imageCount = support.capabilities.minImageCount + 1U;
    if (support.capabilities.maxImageCount > 0 && imageCount > support.capabilities.maxImageCount) {
        imageCount = support.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface_;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    const QueueFamilyIndices indices = findQueueFamilies(physicalDevice_);
    const std::uint32_t queueFamilyIndices[] = {
        indices.graphicsFamily.value(),
        indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = support.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    check(vkCreateSwapchainKHR(device_, &createInfo, nullptr, &swapchain_), "vkCreateSwapchainKHR");

    check(vkGetSwapchainImagesKHR(device_, swapchain_, &imageCount, nullptr), "vkGetSwapchainImagesKHR count");
    swapchainImages_.resize(imageCount);
    check(vkGetSwapchainImagesKHR(device_, swapchain_, &imageCount, swapchainImages_.data()), "vkGetSwapchainImagesKHR data");

    swapchainImageFormat_ = surfaceFormat.format;
    swapchainExtent_ = extent;
}

void VulkanRenderer::createImageViews() {
    swapchainImageViews_.resize(swapchainImages_.size());
    for (std::size_t i = 0; i < swapchainImages_.size(); ++i) {
        swapchainImageViews_[i] = createImageView(swapchainImages_[i], swapchainImageFormat_, VK_IMAGE_ASPECT_COLOR_BIT);
    }
}

void VulkanRenderer::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = swapchainImageFormat_;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentDescription depthAttachment{};
    depthAttachment.format = findDepthFormat();
    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorReference{};
    colorReference.attachment = 0;
    colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthReference{};
    depthReference.attachment = 1;
    depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorReference;
    subpass.pDepthStencilAttachment = &depthReference;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    const std::array<VkAttachmentDescription, 2> attachments{colorAttachment, depthAttachment};
    VkRenderPassCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo.attachmentCount = static_cast<std::uint32_t>(attachments.size());
    createInfo.pAttachments = attachments.data();
    createInfo.subpassCount = 1;
    createInfo.pSubpasses = &subpass;
    createInfo.dependencyCount = 1;
    createInfo.pDependencies = &dependency;

    check(vkCreateRenderPass(device_, &createInfo, nullptr, &renderPass_), "vkCreateRenderPass");
}

void VulkanRenderer::createDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding uniformBinding{};
    uniformBinding.binding = 0;
    uniformBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uniformBinding.descriptorCount = 1;
    uniformBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    VkDescriptorSetLayoutCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    createInfo.bindingCount = 1;
    createInfo.pBindings = &uniformBinding;

    check(vkCreateDescriptorSetLayout(device_, &createInfo, nullptr, &descriptorSetLayout_), "vkCreateDescriptorSetLayout");
}

void VulkanRenderer::createGraphicsPipeline() {
    const VkShaderModule vertexShader = createShaderModule(shaderDirectory_ / "cube.vert.spv");
    const VkShaderModule fragmentShader = createShaderModule(shaderDirectory_ / "cube.frag.spv");

    VkPipelineShaderStageCreateInfo vertexStage{};
    vertexStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertexStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertexStage.module = vertexShader;
    vertexStage.pName = "main";

    VkPipelineShaderStageCreateInfo fragmentStage{};
    fragmentStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragmentStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragmentStage.module = fragmentShader;
    fragmentStage.pName = "main";

    const VkPipelineShaderStageCreateInfo shaderStages[] = {vertexStage, fragmentStage};

    const auto bindingDescription = Vertex::bindingDescription();
    const auto attributeDescriptions = Vertex::attributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInput{};
    vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInput.vertexBindingDescriptionCount = 1;
    vertexInput.pVertexBindingDescriptions = &bindingDescription;
    vertexInput.vertexAttributeDescriptionCount = static_cast<std::uint32_t>(attributeDescriptions.size());
    vertexInput.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkViewport viewport{};
    viewport.x = 0.0F;
    viewport.y = 0.0F;
    viewport.width = static_cast<float>(swapchainExtent_.width);
    viewport.height = static_cast<float>(swapchainExtent_.height);
    viewport.minDepth = 0.0F;
    viewport.maxDepth = 1.0F;

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapchainExtent_;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.cullMode = VK_CULL_MODE_NONE; // Easier for an instructional cube; enable back-face culling after validating winding.
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.lineWidth = 1.0F;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = VK_TRUE;
    depthStencil.depthWriteEnable = VK_TRUE;
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;

    if (pipelineLayout_ == VK_NULL_HANDLE) {
        VkPipelineLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layoutInfo.setLayoutCount = 1;
        layoutInfo.pSetLayouts = &descriptorSetLayout_;
        check(vkCreatePipelineLayout(device_, &layoutInfo, nullptr, &pipelineLayout_), "vkCreatePipelineLayout");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInput;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &depthStencil;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.layout = pipelineLayout_;
    pipelineInfo.renderPass = renderPass_;
    pipelineInfo.subpass = 0;

    check(vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline_), "vkCreateGraphicsPipelines");

    vkDestroyShaderModule(device_, fragmentShader, nullptr);
    vkDestroyShaderModule(device_, vertexShader, nullptr);
}

void VulkanRenderer::createDepthResources() {
    const VkFormat depthFormat = findDepthFormat();
    depthImage_ = createImage(
        swapchainExtent_.width,
        swapchainExtent_.height,
        depthFormat,
        VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    depthImage_.view = createImageView(depthImage_.handle, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

void VulkanRenderer::createFramebuffers() {
    framebuffers_.resize(swapchainImageViews_.size());

    for (std::size_t i = 0; i < swapchainImageViews_.size(); ++i) {
        const std::array<VkImageView, 2> attachments{swapchainImageViews_[i], depthImage_.view};

        VkFramebufferCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        createInfo.renderPass = renderPass_;
        createInfo.attachmentCount = static_cast<std::uint32_t>(attachments.size());
        createInfo.pAttachments = attachments.data();
        createInfo.width = swapchainExtent_.width;
        createInfo.height = swapchainExtent_.height;
        createInfo.layers = 1;

        check(vkCreateFramebuffer(device_, &createInfo, nullptr, &framebuffers_[i]), "vkCreateFramebuffer");
    }
}

void VulkanRenderer::createCommandPool() {
    const QueueFamilyIndices indices = findQueueFamilies(physicalDevice_);

    VkCommandPoolCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    createInfo.queueFamilyIndex = indices.graphicsFamily.value();

    check(vkCreateCommandPool(device_, &createInfo, nullptr, &commandPool_), "vkCreateCommandPool");
}

void VulkanRenderer::loadModel() {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        modelPath_.string(),
        aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_GenSmoothNormals |
            aiProcess_PreTransformVertices |
            aiProcess_ImproveCacheLocality);

    if (scene == nullptr || scene->mRootNode == nullptr || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0U) {
        throw std::runtime_error{"Failed to load model: " + modelPath_.string() + " - " + importer.GetErrorString()};
    }

    vertices_.clear();
    indices_.clear();

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();
    float maxZ = std::numeric_limits<float>::lowest();

    for (std::uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
        const aiMesh* mesh = scene->mMeshes[meshIndex];
        if (mesh == nullptr || !mesh->HasPositions()) {
            continue;
        }

        if (vertices_.size() > std::numeric_limits<std::uint32_t>::max() - mesh->mNumVertices) {
            throw std::runtime_error{"Model is too large for 32-bit index buffers."};
        }

        const std::uint32_t baseVertex = static_cast<std::uint32_t>(vertices_.size());

        for (std::uint32_t i = 0; i < mesh->mNumVertices; ++i) {
            const aiVector3D& p = mesh->mVertices[i];

            Vertex vertex{};
            vertex.position[0] = p.x;
            vertex.position[1] = p.y;
            vertex.position[2] = p.z;

            if (mesh->HasNormals()) {
                const aiVector3D& n = mesh->mNormals[i];
                vertex.color[0] = 0.35F + 0.55F * std::fabs(n.x);
                vertex.color[1] = 0.35F + 0.55F * std::fabs(n.y);
                vertex.color[2] = 0.35F + 0.55F * std::fabs(n.z);
            } else {
                vertex.color[0] = 0.75F;
                vertex.color[1] = 0.75F;
                vertex.color[2] = 0.75F;
            }

            vertices_.push_back(vertex);

            minX = std::min(minX, p.x);
            minY = std::min(minY, p.y);
            minZ = std::min(minZ, p.z);
            maxX = std::max(maxX, p.x);
            maxY = std::max(maxY, p.y);
            maxZ = std::max(maxZ, p.z);
        }

        for (std::uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
            const aiFace& face = mesh->mFaces[faceIndex];
            if (face.mNumIndices != 3U) {
                continue;
            }

            indices_.push_back(baseVertex + face.mIndices[0]);
            indices_.push_back(baseVertex + face.mIndices[1]);
            indices_.push_back(baseVertex + face.mIndices[2]);
        }
    }

    if (vertices_.empty() || indices_.empty()) {
        throw std::runtime_error{"Model did not contain renderable triangle geometry: " + modelPath_.string()};
    }

    const float centerX = (minX + maxX) * 0.5F;
    const float centerY = (minY + maxY) * 0.5F;
    const float centerZ = (minZ + maxZ) * 0.5F;
    const float extentX = maxX - minX;
    const float extentY = maxY - minY;
    const float extentZ = maxZ - minZ;
    const float largestExtent = std::max({extentX, extentY, extentZ, 1.0F});
    const float scale = 2.0F / largestExtent;

    for (auto& vertex : vertices_) {
        vertex.position[0] = (vertex.position[0] - centerX) * scale;
        vertex.position[1] = (vertex.position[1] - centerY) * scale;
        vertex.position[2] = (vertex.position[2] - centerZ) * scale;
    }

    std::cout << "Loaded model: " << modelPath_ << " ("
              << vertices_.size() << " vertices, "
              << indices_.size() << " indices)\n";
}

void VulkanRenderer::createVertexBuffer() {
    const VkDeviceSize bufferSize = sizeof(vertices_[0]) * vertices_.size();
    vertexBuffer_ = createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    void* data = nullptr;
    check(vkMapMemory(device_, vertexBuffer_.memory, 0, bufferSize, 0, &data), "vkMapMemory vertex");
    std::memcpy(data, vertices_.data(), static_cast<std::size_t>(bufferSize));
    vkUnmapMemory(device_, vertexBuffer_.memory);
}

void VulkanRenderer::createIndexBuffer() {
    const VkDeviceSize bufferSize = sizeof(indices_[0]) * indices_.size();
    indexBuffer_ = createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    void* data = nullptr;
    check(vkMapMemory(device_, indexBuffer_.memory, 0, bufferSize, 0, &data), "vkMapMemory index");
    std::memcpy(data, indices_.data(), static_cast<std::size_t>(bufferSize));
    vkUnmapMemory(device_, indexBuffer_.memory);
}

void VulkanRenderer::createUniformBuffers() {
    const VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    for (std::size_t i = 0; i < uniformBuffers_.size(); ++i) {
        uniformBuffers_[i] = createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        check(vkMapMemory(device_, uniformBuffers_[i].memory, 0, bufferSize, 0, &mappedUniformMemory_[i]), "vkMapMemory uniform");
    }
}

void VulkanRenderer::createDescriptorPool() {
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = maxFramesInFlight_;

    VkDescriptorPoolCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.poolSizeCount = 1;
    createInfo.pPoolSizes = &poolSize;
    createInfo.maxSets = maxFramesInFlight_;

    check(vkCreateDescriptorPool(device_, &createInfo, nullptr, &descriptorPool_), "vkCreateDescriptorPool");
}

void VulkanRenderer::createDescriptorSets() {
    const std::array<VkDescriptorSetLayout, maxFramesInFlight_> layouts{
        descriptorSetLayout_,
        descriptorSetLayout_};

    VkDescriptorSetAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool = descriptorPool_;
    allocateInfo.descriptorSetCount = maxFramesInFlight_;
    allocateInfo.pSetLayouts = layouts.data();

    check(vkAllocateDescriptorSets(device_, &allocateInfo, descriptorSets_.data()), "vkAllocateDescriptorSets");

    for (std::size_t i = 0; i < descriptorSets_.size(); ++i) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers_[i].handle;
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = descriptorSets_[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(device_, 1, &descriptorWrite, 0, nullptr);
    }
}

void VulkanRenderer::createCommandBuffers() {
    commandBuffers_.resize(maxFramesInFlight_);

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.commandPool = commandPool_;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandBufferCount = static_cast<std::uint32_t>(commandBuffers_.size());

    check(vkAllocateCommandBuffers(device_, &allocateInfo, commandBuffers_.data()), "vkAllocateCommandBuffers");
}

void VulkanRenderer::createSyncObjects() {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (std::size_t i = 0; i < maxFramesInFlight_; ++i) {
        check(vkCreateSemaphore(device_, &semaphoreInfo, nullptr, &imageAvailableSemaphores_[i]), "vkCreateSemaphore imageAvailable");
        check(vkCreateSemaphore(device_, &semaphoreInfo, nullptr, &renderFinishedSemaphores_[i]), "vkCreateSemaphore renderFinished");
        check(vkCreateFence(device_, &fenceInfo, nullptr, &inFlightFences_[i]), "vkCreateFence inFlight");
    }
}

void VulkanRenderer::cleanupSwapchainResources() {
    for (const auto framebuffer : framebuffers_) {
        vkDestroyFramebuffer(device_, framebuffer, nullptr);
    }
    framebuffers_.clear();

    if (depthImage_.view != VK_NULL_HANDLE) {
        vkDestroyImageView(device_, depthImage_.view, nullptr);
        depthImage_.view = VK_NULL_HANDLE;
    }
    if (depthImage_.handle != VK_NULL_HANDLE) {
        vkDestroyImage(device_, depthImage_.handle, nullptr);
        depthImage_.handle = VK_NULL_HANDLE;
    }
    if (depthImage_.memory != VK_NULL_HANDLE) {
        vkFreeMemory(device_, depthImage_.memory, nullptr);
        depthImage_.memory = VK_NULL_HANDLE;
    }

    if (graphicsPipeline_ != VK_NULL_HANDLE) {
        vkDestroyPipeline(device_, graphicsPipeline_, nullptr);
        graphicsPipeline_ = VK_NULL_HANDLE;
    }

    if (renderPass_ != VK_NULL_HANDLE) {
        vkDestroyRenderPass(device_, renderPass_, nullptr);
        renderPass_ = VK_NULL_HANDLE;
    }

    for (const auto view : swapchainImageViews_) {
        vkDestroyImageView(device_, view, nullptr);
    }
    swapchainImageViews_.clear();

    if (swapchain_ != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(device_, swapchain_, nullptr);
        swapchain_ = VK_NULL_HANDLE;
    }
}

void VulkanRenderer::recreateSwapchainResources() {
    const VkExtent2D drawable = window_.drawableExtent();
    if (drawable.width == 0 || drawable.height == 0) {
        return;
    }

    check(vkDeviceWaitIdle(device_), "vkDeviceWaitIdle before swapchain recreate");
    cleanupSwapchainResources();
    createSwapchainResources();
}

void VulkanRenderer::recordCommandBuffer(VkCommandBuffer commandBuffer, std::uint32_t imageIndex, std::uint32_t frameIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    check(vkBeginCommandBuffer(commandBuffer, &beginInfo), "vkBeginCommandBuffer");

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {{0.02F, 0.02F, 0.03F, 1.0F}};
    clearValues[1].depthStencil = {1.0F, 0};

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass_;
    renderPassInfo.framebuffer = framebuffers_[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapchainExtent_;
    renderPassInfo.clearValueCount = static_cast<std::uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline_);

    const VkBuffer vertexBuffers[] = {vertexBuffer_.handle};
    const VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer_.handle, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindDescriptorSets(
        commandBuffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        pipelineLayout_,
        0,
        1,
        &descriptorSets_[frameIndex],
        0,
        nullptr);
    vkCmdDrawIndexed(commandBuffer, static_cast<std::uint32_t>(indices_.size()), 1, 0, 0, 0);

    vkCmdEndRenderPass(commandBuffer);
    check(vkEndCommandBuffer(commandBuffer), "vkEndCommandBuffer");
}

void VulkanRenderer::updateUniformBuffer(std::uint32_t frameIndex, float elapsedSeconds) {
    const float aspect = static_cast<float>(swapchainExtent_.width) / static_cast<float>(swapchainExtent_.height);
    const math::Mat4 model = math::Mat4::rotationY(elapsedSeconds) * math::Mat4::rotationX(elapsedSeconds * 0.45F);
    const math::Mat4 view = math::Mat4::translation(0.0F, 0.0F, -4.0F);
    const math::Mat4 projection = math::Mat4::perspective(45.0F * 3.1415926535F / 180.0F, aspect, 0.1F, 100.0F);
    const math::Mat4 mvp = projection * view * model;

    UniformBufferObject ubo{};
    std::memcpy(ubo.modelViewProjection, mvp.m.data(), sizeof(ubo.modelViewProjection));
    std::memcpy(mappedUniformMemory_[frameIndex], &ubo, sizeof(ubo));
}

VulkanRenderer::QueueFamilyIndices VulkanRenderer::findQueueFamilies(VkPhysicalDevice device) const {
    QueueFamilyIndices indices{};

    std::uint32_t familyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);
    std::vector<VkQueueFamilyProperties> families(familyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families.data());

    for (std::uint32_t i = 0; i < familyCount; ++i) {
        if ((families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0U) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = VK_FALSE;
        check(vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface_, &presentSupport), "vkGetPhysicalDeviceSurfaceSupportKHR");
        if (presentSupport == VK_TRUE) {
            indices.presentFamily = i;
        }

        if (indices.complete()) {
            break;
        }
    }

    return indices;
}

VulkanRenderer::SwapchainSupport VulkanRenderer::querySwapchainSupport(VkPhysicalDevice device) const {
    SwapchainSupport support{};
    check(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface_, &support.capabilities), "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");

    std::uint32_t formatCount = 0;
    check(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface_, &formatCount, nullptr), "vkGetPhysicalDeviceSurfaceFormatsKHR count");
    support.formats.resize(formatCount);
    if (formatCount > 0) {
        check(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface_, &formatCount, support.formats.data()), "vkGetPhysicalDeviceSurfaceFormatsKHR data");
    }

    std::uint32_t presentModeCount = 0;
    check(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface_, &presentModeCount, nullptr), "vkGetPhysicalDeviceSurfacePresentModesKHR count");
    support.presentModes.resize(presentModeCount);
    if (presentModeCount > 0) {
        check(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface_, &presentModeCount, support.presentModes.data()), "vkGetPhysicalDeviceSurfacePresentModesKHR data");
    }

    return support;
}

bool VulkanRenderer::isDeviceSuitable(VkPhysicalDevice device) const {
    const QueueFamilyIndices indices = findQueueFamilies(device);
    const bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapchainAdequate = false;
    if (extensionsSupported) {
        const SwapchainSupport support = querySwapchainSupport(device);
        swapchainAdequate = !support.formats.empty() && !support.presentModes.empty();
    }

    return indices.complete() && extensionsSupported && swapchainAdequate;
}

bool VulkanRenderer::checkDeviceExtensionSupport(VkPhysicalDevice device) const {
    std::uint32_t extensionCount = 0;
    check(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr), "vkEnumerateDeviceExtensionProperties count");
    std::vector<VkExtensionProperties> available(extensionCount);
    check(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, available.data()), "vkEnumerateDeviceExtensionProperties data");

    std::set<std::string> required(deviceExtensions.begin(), deviceExtensions.end());
    for (const auto& extension : available) {
        required.erase(extension.extensionName);
    }

    return required.empty();
}

VkSurfaceFormatKHR VulkanRenderer::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats) const {
    const auto preferred = std::find_if(formats.begin(), formats.end(), [](const VkSurfaceFormatKHR& format) {
        return format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    });

    return preferred != formats.end() ? *preferred : formats.front();
}

VkPresentModeKHR VulkanRenderer::choosePresentMode(const std::vector<VkPresentModeKHR>& presentModes) const {
    const auto mailbox = std::find(presentModes.begin(), presentModes.end(), VK_PRESENT_MODE_MAILBOX_KHR);
    return mailbox != presentModes.end() ? VK_PRESENT_MODE_MAILBOX_KHR : VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanRenderer::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const {
    if (capabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max()) {
        return capabilities.currentExtent;
    }

    VkExtent2D actual = window_.drawableExtent();
    actual.width = std::clamp(actual.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actual.height = std::clamp(actual.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    return actual;
}

VkFormat VulkanRenderer::findDepthFormat() const {
    return findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

VkFormat VulkanRenderer::findSupportedFormat(
    const std::vector<VkFormat>& candidates,
    VkImageTiling tiling,
    VkFormatFeatureFlags features) const {
    for (const auto format : candidates) {
        VkFormatProperties properties{};
        vkGetPhysicalDeviceFormatProperties(physicalDevice_, format, &properties);

        if (tiling == VK_IMAGE_TILING_LINEAR && (properties.linearTilingFeatures & features) == features) {
            return format;
        }
        if (tiling == VK_IMAGE_TILING_OPTIMAL && (properties.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error{"No supported Vulkan format found."};
}

std::vector<const char*> VulkanRenderer::requiredInstanceExtensions() const {
    unsigned int extensionCount = 0;
    if (SDL_Vulkan_GetInstanceExtensions(window_.nativeHandle(), &extensionCount, nullptr) != SDL_TRUE) {
        throw std::runtime_error{"SDL_Vulkan_GetInstanceExtensions count failed: " + std::string{SDL_GetError()}};
    }

    std::vector<const char*> extensions(extensionCount);
    if (SDL_Vulkan_GetInstanceExtensions(window_.nativeHandle(), &extensionCount, extensions.data()) != SDL_TRUE) {
        throw std::runtime_error{"SDL_Vulkan_GetInstanceExtensions data failed: " + std::string{SDL_GetError()}};
    }

    if (validationEnabled()) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

bool VulkanRenderer::validationLayersAvailable() const {
    std::uint32_t layerCount = 0;
    check(vkEnumerateInstanceLayerProperties(&layerCount, nullptr), "vkEnumerateInstanceLayerProperties count");
    std::vector<VkLayerProperties> available(layerCount);
    check(vkEnumerateInstanceLayerProperties(&layerCount, available.data()), "vkEnumerateInstanceLayerProperties data");

    for (const char* requiredLayer : validationLayers) {
        const bool found = std::any_of(available.begin(), available.end(), [requiredLayer](const VkLayerProperties& layer) {
            return std::strcmp(layer.layerName, requiredLayer) == 0;
        });
        if (!found) {
            return false;
        }
    }

    return true;
}

bool VulkanRenderer::validationEnabled() const noexcept {
#ifndef NDEBUG
    return true;
#else
    return false;
#endif
}

VkShaderModule VulkanRenderer::createShaderModule(const std::filesystem::path& path) const {
    const auto code = readBinaryFile(path);

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const std::uint32_t*>(code.data());

    VkShaderModule shaderModule = VK_NULL_HANDLE;
    check(vkCreateShaderModule(device_, &createInfo, nullptr, &shaderModule), "vkCreateShaderModule " + path.string());
    return shaderModule;
}

std::uint32_t VulkanRenderer::findMemoryType(std::uint32_t typeFilter, VkMemoryPropertyFlags properties) const {
    VkPhysicalDeviceMemoryProperties memoryProperties{};
    vkGetPhysicalDeviceMemoryProperties(physicalDevice_, &memoryProperties);

    for (std::uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {
        const bool typeMatches = (typeFilter & (1U << i)) != 0U;
        const bool propertiesMatch = (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties;
        if (typeMatches && propertiesMatch) {
            return i;
        }
    }

    throw std::runtime_error{"No suitable Vulkan memory type found."};
}

VulkanRenderer::Buffer VulkanRenderer::createBuffer(
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties) const {
    Buffer buffer{};

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    check(vkCreateBuffer(device_, &bufferInfo, nullptr, &buffer.handle), "vkCreateBuffer");

    VkMemoryRequirements requirements{};
    vkGetBufferMemoryRequirements(device_, buffer.handle, &requirements);

    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = requirements.size;
    allocateInfo.memoryTypeIndex = findMemoryType(requirements.memoryTypeBits, properties);

    check(vkAllocateMemory(device_, &allocateInfo, nullptr, &buffer.memory), "vkAllocateMemory buffer");
    check(vkBindBufferMemory(device_, buffer.handle, buffer.memory, 0), "vkBindBufferMemory");

    return buffer;
}

VulkanRenderer::Image VulkanRenderer::createImage(
    std::uint32_t width,
    std::uint32_t height,
    VkFormat format,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkMemoryPropertyFlags properties) const {
    Image image{};

    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = usage;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    check(vkCreateImage(device_, &imageInfo, nullptr, &image.handle), "vkCreateImage");

    VkMemoryRequirements requirements{};
    vkGetImageMemoryRequirements(device_, image.handle, &requirements);

    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = requirements.size;
    allocateInfo.memoryTypeIndex = findMemoryType(requirements.memoryTypeBits, properties);

    check(vkAllocateMemory(device_, &allocateInfo, nullptr, &image.memory), "vkAllocateMemory image");
    check(vkBindImageMemory(device_, image.handle, image.memory, 0), "vkBindImageMemory");

    return image;
}

VkImageView VulkanRenderer::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) const {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = image;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = format;
    createInfo.subresourceRange.aspectMask = aspectFlags;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VkImageView imageView = VK_NULL_HANDLE;
    check(vkCreateImageView(device_, &createInfo, nullptr, &imageView), "vkCreateImageView");
    return imageView;
}

void VulkanRenderer::check(VkResult result, std::string_view operation) {
    if (result != VK_SUCCESS) {
        throw std::runtime_error{std::string{operation} + " failed with VkResult " + std::to_string(static_cast<int>(result))};
    }
}

std::vector<char> VulkanRenderer::readBinaryFile(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error{"Failed to open binary file: " + path.string()};
    }

    const std::streamsize size = file.tellg();
    if (size <= 0) {
        throw std::runtime_error{"Binary file is empty or unreadable: " + path.string()};
    }

    std::vector<char> buffer(static_cast<std::size_t>(size));
    file.seekg(0);
    file.read(buffer.data(), size);
    return buffer;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
    void* /*userData*/) {
    std::cerr << "[Vulkan validation] severity=" << severity
              << " type=" << type
              << " message=" << callbackData->pMessage << '\n';
    return VK_FALSE;
}

} // namespace cube
