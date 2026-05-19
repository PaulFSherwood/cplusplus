# Vulkan Rotating Cube

A small C++20 Vulkan sample that renders a rotating indexed cube through an SDL2 window. The code is intentionally organized like a real project instead of a single tutorial file.

## What this demonstrates

- Vulkan instance, device, queue, and surface setup
- SDL2 window integration
- Swapchain creation and recreation on resize
- Render pass, graphics pipeline, framebuffers, and command buffers
- Vertex, index, and uniform buffers
- Descriptor sets for per-frame transform data
- Depth buffering
- GLSL to SPIR-V shader compilation through `glslc`
- Two frames in flight with semaphores and fences

## Build

Linux/Kubuntu example:

```bash
sudo apt install build-essential cmake pkg-config libsdl2-dev
```

Install the Vulkan SDK from LunarG, then source its environment script if using the tarball installer:

```bash
source ~/vulkan/1.x.xxx.x/setup-env.sh
```

Then build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
cd build/bin
./vulkan_rotating_cube
```

The executable expects the compiled SPIR-V shaders in `./shaders/`. CMake creates that folder under `build/bin/shaders`.

## Notes

This sample uses host-visible buffers for vertex and index data to keep the code readable. A production renderer would usually upload static mesh data with staging buffers into device-local memory.
