# Companion Document: Vulkan Rotating Cube

## 1. Purpose

This project is a deliberately small Vulkan renderer that still follows professional structure. The goal is not to hide Vulkan complexity, but to divide it into readable subsystems so the project can grow into a renderer, simulator viewer, ship interior viewer, or C++ portfolio project.

## 2. Runtime Flow

```text
main
 └── App
      ├── SdlWindow
      └── VulkanRenderer
           ├── Instance / validation
           ├── Surface
           ├── Physical device selection
           ├── Logical device and queues
           ├── Swapchain resources
           ├── Buffers and descriptors
           ├── Command buffers
           └── Synchronization objects
```

Each frame:

```text
Poll SDL events
Update elapsed time
Wait for current frame fence
Acquire swapchain image
Update uniform buffer
Record command buffer
Submit graphics work
Present image
Advance frame index
```

## 3. Important Vulkan Concepts

### Instance

The instance is the connection between the application and the Vulkan loader. SDL provides the platform-specific extensions needed to create a window surface.

### Surface

The surface is the Vulkan representation of the SDL window. The swapchain is created against this surface.

### Physical Device

The renderer selects a GPU that supports:

- graphics queue
- present queue
- swapchain extension
- usable surface formats and present modes

### Logical Device

The logical device exposes queues and device-level Vulkan functions. This project creates one graphics queue and one present queue, even if they point to the same queue family.

### Swapchain

The swapchain owns the images that are presented to the window. It must be recreated when the window is resized or when presentation reports that the old swapchain is out of date.

Swapchain-owned resources in this sample:

- swapchain
- swapchain image views
- render pass
- graphics pipeline
- depth image
- framebuffers

### Pipeline

The graphics pipeline defines how vertices become pixels. In this project it includes:

- vertex shader
- fragment shader
- vertex input layout
- input assembly
- viewport and scissor
- rasterization
- depth testing
- color blending
- render pass compatibility

### Buffers

The project uses three buffer types:

- vertex buffer: cube vertex positions and colors
- index buffer: cube triangle indices
- uniform buffers: per-frame model-view-projection matrix

For clarity, static mesh buffers are host-visible. A more advanced version should upload them through staging buffers into device-local memory.

### Descriptors

The descriptor set binds the uniform buffer to the vertex shader at binding 0.

There are two descriptor sets because there are two frames in flight.

### Synchronization

Each frame uses:

- image-available semaphore
- render-finished semaphore
- in-flight fence

The fence prevents the CPU from overwriting per-frame resources that the GPU may still be using.

## 4. Why This Is Structured This Way

The main separation is between platform ownership and renderer ownership.

`SdlWindow` owns SDL initialization and the native window.

`VulkanRenderer` owns every Vulkan handle. That makes cleanup order easier to audit.

The swapchain has its own lifetime group because resize handling is one of the first places Vulkan samples become messy.

## 5. Suggested Next Steps

### Step 1: Add a camera class

Move view/projection logic out of `VulkanRenderer::updateUniformBuffer`.

### Step 2: Add mesh abstraction

Create a `Mesh` type that owns a vertex buffer, index buffer, and index count.

### Step 3: Add staging buffers

Replace host-visible vertex/index buffers with staging uploads into device-local memory.

### Step 4: Add dynamic viewport/scissor

Make the pipeline less dependent on swapchain extent.

### Step 5: Add ImGui

Use it for frame timing, renderer settings, and debug toggles.

### Step 6: Add scene objects

Create a simple scene list:

```text
Scene
 ├── Entity 1: cube mesh + transform
 ├── Entity 2: cube mesh + transform
 └── Entity 3: imported mesh + transform
```

### Step 7: Add model loading

Use a controlled format first, such as OBJ, before jumping into glTF.

## 6. Review Checklist

Before treating this as portfolio code, verify:

- Debug build runs clean with validation layers.
- Resize does not crash.
- Closing the window exits cleanly.
- Shaders rebuild when GLSL files change.
- The code builds from a clean clone using documented commands.
- Every owning class has clear destruction behavior.

## FPS Counter

The application layer reports frames per second in the SDL window title. The
renderer stays focused on Vulkan ownership and frame submission; the app loop
counts completed frames and updates the title roughly twice per second. This is
intentional separation: diagnostics that belong to the UI shell should not be
mixed into Vulkan device, swapchain, or pipeline code.
