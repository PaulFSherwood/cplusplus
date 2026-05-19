# EDUCATIONAL.md — Learning the Vulkan Krait Model Viewer From Scratch

## Purpose

This document teaches a new developer how this project works from the ground up.

The goal is not only to explain the existing code. The goal is to help someone rebuild the project in stages while learning:

- Basic C++ project structure
- CMake
- SDL2 window creation
- Vulkan concepts
- Shader compilation
- Vertex and index buffers
- Uniform buffers
- Depth buffering
- Model loading with Assimp
- Application loop structure
- Asset paths and runtime layout
- Debugging and validation layers

This document assumes the reader is new to C++, SDL2, and Vulkan.

By the end, the developer should understand the major ideas well enough to recreate a simplified version of the project from scratch.

---

# 1. What This Project Is

This project is a small Vulkan renderer.

It opens a window, initializes Vulkan, loads shaders, creates GPU buffers, and draws either a simple mesh or a model such as:

```text
assets/models/KraitPhantom.glb
```

The project is intentionally small, but it already contains many real engine-style ideas:

```text
Application
 ├── Window system
 ├── Renderer
 ├── Vulkan setup
 ├── Shaders
 ├── Mesh/model data
 ├── GPU buffers
 ├── Uniform data
 ├── Render loop
 └── Runtime assets
```

The important thing to understand is that Vulkan does not draw anything automatically. Almost everything must be described explicitly.

That is why Vulkan code looks large compared to SDL, OpenGL, or simple game frameworks.

---

# 2. Big Picture Runtime Flow

When the program starts, it roughly does this:

```text
main()
 └── App::run()
      ├── Create SDL window
      ├── Decide runtime asset paths
      ├── Create VulkanRenderer
      │    ├── Create Vulkan instance
      │    ├── Create window surface
      │    ├── Pick GPU
      │    ├── Create logical device
      │    ├── Create swapchain
      │    ├── Create render pass
      │    ├── Create graphics pipeline
      │    ├── Load model
      │    ├── Create vertex/index buffers
      │    ├── Create uniform buffers
      │    ├── Create command buffers
      │    └── Create synchronization objects
      ├── Loop until user quits
      │    ├── Poll SDL events
      │    ├── Update rotation/time
      │    ├── Draw frame
      │    └── Update FPS title
      └── Clean up
```

The biggest mental shift is this:

```text
SDL owns the window.
Vulkan owns the rendering.
The App owns the loop.
```

---

# 3. Project Layout

A good project layout keeps responsibilities separate.

Example layout:

```text
vulkan_rotating_cube/
├── CMakeLists.txt
├── README.md
├── EDUCATIONAL.md
├── assets/
│   └── models/
│       └── KraitPhantom.glb
├── shaders/
│   ├── cube.vert
│   └── cube.frag
└── src/
    ├── main.cpp
    ├── App.hpp
    ├── App.cpp
    ├── platform/
    │   ├── SdlWindow.hpp
    │   └── SdlWindow.cpp
    ├── graphics/
    │   ├── VulkanRenderer.hpp
    │   └── VulkanRenderer.cpp
    └── math/
        └── Mat4.hpp
```

## File Responsibilities

### `main.cpp`

This should stay small.

It should create the application object and run it.

```cpp
int main(int argc, char** argv) {
    cube::App app;
    return app.run(argc, argv);
}
```

`main.cpp` should not contain Vulkan setup.

---

### `App.cpp`

`App` owns the high-level application flow.

It decides:

- Window title
- Window size
- Where runtime assets are located
- When to quit
- How to update frame timing
- When to call the renderer

`App` should not know the details of swapchains, render passes, or vertex buffers.

---

### `SdlWindow.cpp`

`SdlWindow` owns the SDL window.

It should handle:

- `SDL_Init`
- `SDL_CreateWindow`
- `SDL_DestroyWindow`
- Window title updates
- Vulkan surface support helpers

It should not know how to draw models.

---

### `VulkanRenderer.cpp`

`VulkanRenderer` owns the Vulkan rendering system.

It handles:

- Vulkan instance
- Validation layers
- Physical device selection
- Logical device creation
- Swapchain
- Render pass
- Graphics pipeline
- Shader modules
- Vertex/index buffers
- Uniform buffers
- Command buffers
- Synchronization
- Drawing

This is the largest file because Vulkan requires many setup steps.

---

### `Mat4.hpp`

This is a small math helper.

It usually contains:

- Matrix identity
- Perspective projection
- Rotation
- Translation
- Matrix multiply

A real project might use GLM, but a small custom math header is useful for learning.

---

# 4. Stage 0 — Learn What a C++ Program Is

Before Vulkan, the developer should understand the shape of a basic C++ program.

A minimum C++ program:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world\n";
    return 0;
}
```

## Key Ideas

- `main()` is where the program starts.
- `#include` brings in declarations from another file.
- `std::cout` prints text.
- `return 0` means successful exit.

## Questions

1. What function does a C++ program start from?
2. What does `#include <iostream>` do?
3. What does `return 0` mean?
4. What is the difference between source code and an executable?

## Assignment

Write a program called `hello.cpp` that prints:

```text
Vulkan training begins.
```

Compile it manually:

```bash
g++ hello.cpp -o hello
./hello
```

---

# 5. Stage 1 — Learn Header and Source Files

C++ projects usually split code into headers and source files.

Example:

```text
Greeter.hpp
Greeter.cpp
main.cpp
```

`Greeter.hpp` declares what exists.

```cpp
#pragma once

#include <string>

class Greeter {
public:
    explicit Greeter(std::string name);
    void sayHello() const;

private:
    std::string name_;
};
```

`Greeter.cpp` defines how it works.

```cpp
#include "Greeter.hpp"

#include <iostream>
#include <utility>

Greeter::Greeter(std::string name)
    : name_{std::move(name)} {
}

void Greeter::sayHello() const {
    std::cout << "Hello, " << name_ << "\n";
}
```

`main.cpp` uses it.

```cpp
#include "Greeter.hpp"

int main() {
    Greeter greeter{"Pilot"};
    greeter.sayHello();
}
```

## Key Ideas

- `.hpp` files usually contain declarations.
- `.cpp` files usually contain implementations.
- Class member variables usually belong inside the class.
- Do not define normal global variables in headers unless you know why.

## Common Mistake

Bad:

```cpp
// In a header file
std::filesystem::path shaderDirectory_;
```

That creates a global variable in every `.cpp` file that includes the header.

Good:

```cpp
class VulkanRenderer {
private:
    std::filesystem::path shaderDirectory_;
};
```

## Questions

1. What is the purpose of a header file?
2. What is the purpose of a source file?
3. Why is a global variable in a header dangerous?
4. What does a constructor do?

## Assignment

Write a `Counter` class with:

```text
Counter.hpp
Counter.cpp
main.cpp
```

Requirements:

- `Counter` starts at zero.
- `increment()` adds one.
- `value()` returns the current count.
- `main()` increments it three times and prints the result.

---

# 6. Stage 2 — Learn CMake

CMake generates build files.

Instead of compiling every `.cpp` manually, you describe the project once.

Simple `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.22)

project(MyProgram LANGUAGES CXX)

add_executable(my_program
    src/main.cpp
    src/Counter.cpp
)

target_compile_features(my_program PRIVATE cxx_std_20)
```

Then build:

```bash
cmake -S . -B build
cmake --build build -j
./build/my_program
```

## Key Ideas

- `cmake -S . -B build` configures the project.
- `cmake --build build` builds it.
- `add_executable()` creates a program.
- `target_compile_features()` selects the C++ standard.

## Questions

1. What is the difference between configuring and building?
2. Why do we use a `build/` directory?
3. What does `add_executable()` do?
4. Why should `build/` usually be in `.gitignore`?

## Assignment

Convert your `Counter` program to use CMake.

---

# 7. Stage 3 — Learn SDL2 Window Creation

SDL2 gives us a cross-platform way to create a window.

For Vulkan, SDL must create a Vulkan-capable window.

The important flag is:

```cpp
SDL_WINDOW_VULKAN
```

A window wrapper class is useful because it gives ownership a clear home.

Example responsibility:

```text
SdlWindow
 ├── initializes SDL
 ├── creates SDL_Window
 ├── destroys SDL_Window
 ├── exposes width/height
 ├── updates title
 └── helps Vulkan create a surface
```

## Why Wrap SDL?

Instead of letting the whole program use raw `SDL_Window*`, we hide it inside a class.

That makes the rest of the program cleaner.

## Questions

1. What does SDL2 provide in this project?
2. Why does the SDL window need the `SDL_WINDOW_VULKAN` flag?
3. Why is it useful to wrap `SDL_Window*` inside a class?
4. Should `SdlWindow` draw the model? Why or why not?

## Assignment

Write a program that:

- Opens an SDL2 window.
- Keeps it open until the user closes it.
- Updates the window title once per second with an increasing number.

Do not use Vulkan yet.

---

# 8. Stage 4 — Understand the App Loop

A game or graphics program usually has a loop.

Basic loop:

```text
while running:
    handle input
    update time
    render frame
```

In this project:

```text
App::run()
 ├── poll SDL events
 ├── update rotation
 ├── draw frame
 └── update FPS title
```

## FPS Counter Idea

FPS means frames per second.

A simple FPS counter:

```text
frameCount += 1

if half a second passed:
    fps = frameCount / elapsedSeconds
    update window title
    reset counter
```

## Questions

1. Why does the program need a loop?
2. What is the difference between input, update, and render?
3. Why should FPS update once or twice per second instead of every frame?
4. Why does the renderer not own the FPS window title?

## Assignment

Modify your SDL window program:

- Count frames.
- Update the window title with approximate FPS.
- Cap nothing manually yet.

---

# 9. Stage 5 — Vulkan Mental Model

Vulkan is explicit.

That means the programmer must describe nearly everything.

A simplified Vulkan chain:

```text
Instance
 └── Physical Device
      └── Logical Device
           └── Queues
                └── Swapchain
                     └── Images
                          └── Render Pass
                               └── Pipeline
                                    └── Command Buffers
```

## Important Terms

### Vulkan Instance

Represents the Vulkan library connection for your application.

### Physical Device

The actual GPU.

### Logical Device

Your program's interface to the GPU.

### Queue

A place where command buffers are submitted.

### Surface

The connection between Vulkan and the window.

### Swapchain

A set of images that are presented to the screen.

### Render Pass

Describes how rendering attachments are used.

### Pipeline

Describes how vertices become pixels.

### Command Buffer

A recorded list of GPU commands.

## Questions

1. What is the difference between a physical device and a logical device?
2. What does the swapchain contain?
3. What is a command buffer?
4. Why does Vulkan need a surface?

## Assignment

Do not write code yet. Draw this diagram by hand:

```text
SDL Window -> Vulkan Surface -> Swapchain -> Render Pass -> Pipeline -> Command Buffer
```

Then write one sentence explaining each arrow.

---

# 10. Stage 6 — Validation Layers

Vulkan validation layers help catch mistakes.

Debug builds often request:

```text
VK_LAYER_KHRONOS_validation
```

If the layer is missing, the program may print:

```text
Validation layers requested, but VK_LAYER_KHRONOS_validation is not available.
```

On Ubuntu/Kubuntu, install:

```bash
sudo apt install vulkan-validationlayers vulkan-tools
```

Then check:

```bash
vulkaninfo | grep VK_LAYER_KHRONOS_validation
```

## Key Idea

Vulkan itself does not protect you from many mistakes.

Validation layers are like a Vulkan safety inspector.

## Questions

1. Why are validation layers useful?
2. Should validation layers usually be enabled in Release builds?
3. What does `VK_LAYER_KHRONOS_validation` do?
4. What tool can show available Vulkan layers?

## Assignment

Run:

```bash
vulkaninfo | less
```

Find:

- Your GPU name
- Vulkan version
- Available layers

Write them down in a file called `notes/vulkan_system.md`.

---

# 11. Stage 7 — Shaders

Shaders are small programs that run on the GPU.

This project has:

```text
shaders/cube.vert
shaders/cube.frag
```

### Vertex Shader

Runs for each vertex.

It usually handles:

- Position
- Transformation matrices
- Passing color/UV/normal data forward

### Fragment Shader

Runs for pixels/fragments.

It usually handles:

- Final color
- Texture sampling
- Lighting result

GLSL shaders are compiled into SPIR-V:

```text
cube.vert -> cube.vert.spv
cube.frag -> cube.frag.spv
```

The project uses `glslc`.

Install if needed:

```bash
sudo apt install glslc
```

## Questions

1. What does a vertex shader do?
2. What does a fragment shader do?
3. What is SPIR-V?
4. Why does CMake compile shaders before running the program?

## Assignment

Change the fragment shader to output a different flat color.

Rebuild and run.

Expected result:

- The model/cube changes color.

---

# 12. Stage 8 — Runtime Paths and Asset Copying

One bug this project hit was:

```text
Failed to open binary file: shaders/cube.vert.spv
```

That happened because the program looked for assets relative to the shell's current directory.

A better approach is:

```text
Find the executable's directory.
Load shaders relative to the executable.
```

On Linux:

```cpp
std::filesystem::path executableDirectory() {
    std::array<char, 4096> buffer{};

    const ssize_t count =
        readlink("/proc/self/exe", buffer.data(), buffer.size() - 1);

    if (count <= 0) {
        return std::filesystem::current_path();
    }

    buffer[static_cast<std::size_t>(count)] = '\0';

    return std::filesystem::path{buffer.data()}.parent_path();
}
```

Then:

```cpp
const auto shaderDirectory = executableDirectory() / "shaders";
const auto modelPath =
    executableDirectory() / "assets" / "models" / "KraitPhantom.glb";
```

## Key Idea

Do not assume the user runs the program from a specific folder.

This should work:

```bash
./build/bin/vulkan_rotating_cube
```

and this should also work:

```bash
cd build/bin
./vulkan_rotating_cube
```

## Questions

1. What is the difference between the current working directory and the executable directory?
2. Why did `shaders/cube.vert.spv` fail from the project root?
3. Why should runtime assets be copied into `build/bin`?
4. Why is hardcoding relative paths fragile?

## Assignment

Write a small C++ program that prints:

- Current working directory
- Executable directory

Run it from two different folders and compare the output.

---

# 13. Stage 9 — Vertex Data

A mesh is made of vertices.

A simple vertex might contain:

```cpp
struct Vertex {
    float position[3];
    float color[3];
};
```

A more advanced vertex might contain:

```cpp
struct Vertex {
    float position[3];
    float normal[3];
    float uv[2];
};
```

The current basic renderer may only use position/color at first.

For textured models, UVs are required.

## Vertex Buffer

A vertex buffer stores vertex data on the GPU.

## Index Buffer

An index buffer tells Vulkan which vertices form triangles.

Example:

```text
vertices:
0, 1, 2, 3

indices:
0, 1, 2
2, 3, 0
```

That draws two triangles using four vertices.

## Questions

1. What is a vertex?
2. What is an index?
3. Why use indices instead of duplicating vertices?
4. What extra vertex data is needed for textures?

## Assignment

Create a simple mesh by hand:

- Four vertices
- Six indices
- Shape: square made from two triangles

Print the vertices and triangle indices to the terminal.

No Vulkan required.

---

# 14. Stage 10 — Buffers and GPU Memory

In Vulkan, data must be copied to GPU-accessible memory.

Common flow:

```text
CPU vector<Vertex>
 └── staging buffer
      └── GPU vertex buffer
```

Why not always use CPU-visible memory?

Because fast GPU memory is often not directly convenient for the CPU to write to.

So we use staging:

```text
CPU writes staging buffer.
GPU copies staging buffer into fast device-local buffer.
Renderer draws from device-local buffer.
```

## Questions

1. What is a GPU buffer?
2. What is a staging buffer?
3. Why use device-local memory?
4. Why does Vulkan require explicit memory handling?

## Assignment

Write a plain C++ program that simulates staging:

```text
vector<int> cpuData
vector<int> stagingData
vector<int> gpuData
```

Copy data from CPU to staging to GPU.

Print each stage.

---

# 15. Stage 11 — Uniform Buffers

A uniform buffer stores data that shaders need every frame.

For a rotating object, common uniform data includes:

```cpp
struct UniformBufferObject {
    Mat4 model;
    Mat4 view;
    Mat4 projection;
};
```

### Model Matrix

Places the object in the world.

### View Matrix

Represents the camera.

### Projection Matrix

Turns 3D camera space into screen space.

The render loop updates the uniform buffer each frame so the model rotates.

## Questions

1. What is a uniform buffer?
2. What does the model matrix do?
3. What does the view matrix do?
4. What does the projection matrix do?
5. Why does rotation belong in the model matrix?

## Assignment

Write a program using your `Mat4` type that:

- Creates an identity matrix.
- Creates a rotation matrix.
- Prints both.

Then change the rotation angle over time and print the angle every frame.

---

# 16. Stage 12 — Depth Buffer

A depth buffer stores how far each pixel is from the camera.

Without depth testing, triangles may draw in the wrong order.

A cube might still appear acceptable sometimes.

A real ship model will usually look broken without depth testing.

## Depth Testing

Depth testing answers:

```text
Is this new pixel closer than the pixel already drawn here?
```

If yes, draw it.

If no, discard it.

## Questions

1. What problem does a depth buffer solve?
2. Why might a cube look okay without depth testing?
3. Why does a complex model need depth testing?
4. What kind of image is the depth buffer?

## Assignment

Write a plain English explanation of why drawing two triangles in the wrong order can make 3D look incorrect.

Then sketch two overlapping triangles and label which one should appear in front.

---

# 17. Stage 13 — Graphics Pipeline

The graphics pipeline describes how Vulkan draws.

Simplified:

```text
Vertex input
 └── Vertex shader
      └── Input assembly
           └── Rasterization
                └── Fragment shader
                     └── Color/depth output
```

The pipeline includes:

- Shader stages
- Vertex format
- Triangle topology
- Viewport/scissor
- Rasterizer settings
- Depth/stencil settings
- Color blending

## Important Concept

In Vulkan, pipelines are mostly fixed after creation.

If you need a very different way to draw, you often create another pipeline.

## Questions

1. What does the graphics pipeline describe?
2. Why does Vulkan need to know the vertex format?
3. What is triangle topology?
4. Why is pipeline creation considered expensive?

## Assignment

Open `VulkanRenderer.cpp`.

Find `createGraphicsPipeline()`.

Write a short comment above each major block explaining what it configures.

---

# 18. Stage 14 — Command Buffers

Vulkan does not immediately draw when you call a draw function.

You record commands into a command buffer.

Example flow:

```text
Begin command buffer
 ├── Begin render pass
 ├── Bind pipeline
 ├── Bind vertex buffer
 ├── Bind index buffer
 ├── Bind descriptor sets
 ├── Draw indexed
 └── End render pass
End command buffer
```

Then the command buffer is submitted to a queue.

## Questions

1. What is a command buffer?
2. Why does Vulkan record commands instead of drawing immediately?
3. What does `vkCmdBindPipeline` do?
4. What does `vkCmdDrawIndexed` do?

## Assignment

In `recordCommandBuffer()`, find the draw call.

Add comments explaining:

- When the render pass begins
- Where the pipeline is bound
- Where vertex/index buffers are bound
- Where drawing happens

---

# 19. Stage 15 — Synchronization

Rendering uses CPU and GPU work.

The CPU may prepare commands while the GPU is still rendering a previous frame.

Vulkan synchronization prevents resource conflicts.

Common objects:

```text
Semaphore
Fence
```

### Semaphore

Used between GPU operations.

Example:

```text
Wait until image is available before rendering.
Wait until rendering is done before presenting.
```

### Fence

Used between CPU and GPU.

Example:

```text
CPU waits until a frame's GPU work is complete.
```

## Questions

1. What is a semaphore?
2. What is a fence?
3. Why can't the CPU freely reuse command buffers whenever it wants?
4. What does "frames in flight" mean?

## Assignment

Draw a timeline:

```text
CPU frame 1
GPU frame 1
CPU frame 2
GPU frame 2
```

Mark where a fence might be needed.

---

# 20. Stage 16 — Loading a Model With Assimp

Assimp loads many model formats.

In this project, the chosen model is:

```text
assets/models/KraitPhantom.glb
```

The high-level flow:

```text
App.cpp
 └── chooses modelPath
      └── passes modelPath to VulkanRenderer
           └── VulkanRenderer::loadModel()
                ├── Assimp reads file
                ├── collect vertices
                ├── collect indices
                ├── normalize model scale
                └── create GPU buffers
```

## What Usually Loads First

The first model-loading stage usually loads only:

- positions
- triangles
- maybe vertex color

It may not load:

- textures
- Blender materials
- complex node animations
- lights
- cameras
- shader graphs

That is normal.

Rendering textured models requires more systems.

## Questions

1. What is Assimp used for?
2. What file decides which model path to use?
3. What function actually loads the model?
4. Why might the model look different from Blender?
5. Why is `.glb` better for runtime than `.blend`?

## Assignment

Change the model path in `App.cpp` to a different model file.

Requirements:

- Put the model in `assets/models/`
- Update `modelPath`
- Rebuild
- Run

Write down what changed visually.

---

# 21. Stage 17 — Why Textures Are a Separate Upgrade

Seeing the model shape is not the same as seeing the Blender material.

For textured rendering, the engine needs:

```text
UV coordinates
image file loading
Vulkan image creation
image memory
image view
sampler
descriptor binding
fragment shader texture sampling
material-to-mesh assignment
```

A fragment shader for a flat color might do:

```glsl
outColor = vec4(0.7, 0.7, 0.7, 1.0);
```

A texture shader does something more like:

```glsl
outColor = texture(albedoTexture, fragUv);
```

That requires a texture descriptor to be bound.

## Questions

1. What are UV coordinates?
2. What is a Vulkan image?
3. What is a sampler?
4. Why does the shader need to change for textures?
5. Why should texture loading wait until geometry loading works?

## Assignment

Before adding Vulkan textures, inspect your GLB:

```bash
assimp info assets/models/KraitPhantom.glb
```

Write down:

- Number of meshes
- Number of materials
- Whether textures are listed

---

# 22. Stage 18 — Asset Ownership

A project with assets needs a policy.

Recommended:

```text
Commit:
  src/
  shaders/*.vert
  shaders/*.frag
  assets/models/small_test_model.glb
  CMakeLists.txt
  docs/

Do not commit:
  build/
  *.o
  generated *.spv
```

For larger assets, use Git LFS:

```bash
git lfs track "*.blend"
git lfs track "*.glb"
git lfs track "*.fbx"
git add .gitattributes
```

## Questions

1. Why should `build/` not be committed?
2. Why should generated `.spv` files usually not be committed?
3. What is Git LFS for?
4. Should `.blend` be treated as source art or runtime data?

## Assignment

Create a `.gitignore` containing:

```gitignore
build/
*.o
*.a
*.so
*.spv
```

Then run:

```bash
git status
```

Verify that `build/` is not listed.

---

# 23. Stage 19 — Suggested Learning Order for This Project

Do not try to understand all of Vulkan at once.

Use this order:

```text
1. main.cpp
2. App.cpp
3. SdlWindow.hpp/.cpp
4. CMakeLists.txt
5. shaders/
6. VulkanRenderer constructor
7. createInstance()
8. createSurface()
9. pickPhysicalDevice()
10. createLogicalDevice()
11. createSwapchain()
12. createRenderPass()
13. createGraphicsPipeline()
14. loadModel()
15. createVertexBuffer()
16. createIndexBuffer()
17. createUniformBuffers()
18. recordCommandBuffer()
19. drawFrame()
20. cleanup/destructor
```

This order moves from easiest to hardest.

## Questions

1. Why should a beginner start with `main.cpp` instead of `VulkanRenderer.cpp`?
2. Which file owns the event loop?
3. Which file owns Vulkan setup?
4. Which function is probably the best place to study actual draw commands?

## Assignment

Make a file called:

```text
notes/code_walkthrough.md
```

For each file, write:

```text
File:
Purpose:
Most important function:
One thing I do not understand yet:
```

---

# 24. Stage 20 — Rebuild the Project From Scratch

A developer who truly understands this project should be able to rebuild it in small stages.

## Rebuild Plan

### Step 1

Create a CMake C++ project.

Success condition:

```text
Program prints hello.
```

### Step 2

Add `App`.

Success condition:

```text
main.cpp only creates App and calls run().
```

### Step 3

Add SDL window.

Success condition:

```text
Window opens and closes correctly.
```

### Step 4

Add FPS title update.

Success condition:

```text
Window title shows FPS.
```

### Step 5

Add Vulkan instance and validation layers.

Success condition:

```text
Program creates Vulkan instance without rendering.
```

### Step 6

Add SDL Vulkan surface.

Success condition:

```text
Program creates a Vulkan surface for the SDL window.
```

### Step 7

Pick physical device and create logical device.

Success condition:

```text
Program prints selected GPU name.
```

### Step 8

Create swapchain.

Success condition:

```text
Program creates swapchain images.
```

### Step 9

Create render pass and framebuffers.

Success condition:

```text
Program clears screen to a color.
```

### Step 10

Create shaders and graphics pipeline.

Success condition:

```text
Program renders a triangle.
```

### Step 11

Add vertex and index buffers.

Success condition:

```text
Program renders a square or cube.
```

### Step 12

Add uniform buffer rotation.

Success condition:

```text
Cube rotates.
```

### Step 13

Add depth buffer.

Success condition:

```text
3D cube faces render correctly.
```

### Step 14

Add Assimp.

Success condition:

```text
Program loads model and prints vertex/index count.
```

### Step 15

Draw the model.

Success condition:

```text
Krait model appears in the window.
```

### Step 16

Add camera controls.

Success condition:

```text
User can move around the model.
```

### Step 17

Add textures.

Success condition:

```text
Model uses texture/material color instead of flat color.
```

---

# 25. Current Project Training Checklist

Use this checklist to train on the existing code.

## Basic Build

- [ ] Can configure with CMake.
- [ ] Can build with CMake.
- [ ] Can run from project root.
- [ ] Can run from build/bin.
- [ ] Can explain why both should work.

## SDL

- [ ] Can explain why SDL is used.
- [ ] Can find where the window is created.
- [ ] Can find where events are polled.
- [ ] Can change the window title.

## Vulkan Setup

- [ ] Can find where the Vulkan instance is created.
- [ ] Can explain validation layers.
- [ ] Can find where the physical GPU is selected.
- [ ] Can find where the logical device is created.
- [ ] Can find where the swapchain is created.

## Shaders

- [ ] Can find the vertex shader.
- [ ] Can find the fragment shader.
- [ ] Can explain `.spv`.
- [ ] Can change the fragment color.

## Drawing

- [ ] Can find `recordCommandBuffer()`.
- [ ] Can find `vkCmdDrawIndexed`.
- [ ] Can explain vertex buffer.
- [ ] Can explain index buffer.

## Model Loading

- [ ] Can find `modelPath` in `App.cpp`.
- [ ] Can find `loadModel()` in `VulkanRenderer.cpp`.
- [ ] Can explain why the model may not look like Blender yet.
- [ ] Can replace the model with another `.glb`.

## FPS

- [ ] Can find the FPS counter code.
- [ ] Can explain why FPS is probably near 60.
- [ ] Can explain display refresh/vsync at a basic level.

---

# 26. Final Capstone Exercise

When the developer finishes this document, they should build a small independent project.

## Assignment: Model Viewer Lite

Create a new project called:

```text
model_viewer_lite
```

Requirements:

1. Uses CMake.
2. Uses SDL2.
3. Opens a Vulkan-capable window.
4. Initializes Vulkan validation layers in Debug.
5. Clears the screen to a color.
6. Renders a triangle.
7. Renders an indexed cube.
8. Adds rotation with a uniform buffer.
9. Adds depth testing.
10. Loads a `.glb` model with Assimp.
11. Displays FPS in the window title.
12. Loads shaders relative to the executable directory.
13. Has a `README.md`.
14. Has a `.gitignore`.
15. Has comments explaining every major Vulkan setup phase.

## Oral Review Questions

The developer should be able to answer these without looking:

1. What does SDL do in this project?
2. What does Vulkan do in this project?
3. What does CMake do in this project?
4. What is a swapchain?
5. What is a render pass?
6. What is a graphics pipeline?
7. What is a command buffer?
8. What is a vertex buffer?
9. What is an index buffer?
10. What is a uniform buffer?
11. What is a depth buffer?
12. What does Assimp do?
13. Why might a GLB model look different from Blender?
14. Why should runtime paths be based on the executable directory?
15. Why should `build/` not be committed?

---

# 27. Recommended Next Features

After the model loads correctly, add features in this order:

```text
1. Camera controls
2. Better model normalization
3. Wireframe toggle
4. Model statistics overlay
5. Basic directional lighting
6. Normals
7. Texture loading
8. Material loading
9. Multiple meshes
10. Scene graph / node transforms
```

The best next training feature is probably:

```text
Camera controls
```

Because it teaches:

- Input handling
- View matrix changes
- Separation between model transform and camera transform
- Real interactive debugging

---

# 28. One-Sentence Summary

This project is a small engine-style Vulkan program where SDL creates the window, the App owns the loop, VulkanRenderer owns GPU rendering, shaders define GPU behavior, Assimp loads model geometry, and CMake builds/copies the runtime pieces needed to run it.
