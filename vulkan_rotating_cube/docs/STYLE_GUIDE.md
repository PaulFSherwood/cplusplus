# Style Guide

## Language

- C++20.
- Prefer RAII ownership wrappers at system boundaries.
- Use exceptions for initialization failures and unrecoverable graphics setup errors.
- Keep Vulkan handles initialized to `VK_NULL_HANDLE`.
- Delete copy/move operations for owning classes unless ownership transfer is deliberately designed.

## Naming

- Types use `PascalCase`: `VulkanRenderer`, `SdlWindow`.
- Functions and local variables use `camelCase`: `createSwapchain`, `imageIndex`.
- Private member variables end with `_`: `device_`, `swapchain_`.
- Constants use descriptive lower camel/snake hybrid only where readability benefits: `maxFramesInFlight_`.

## File Organization

- `platform/` owns OS/windowing integration.
- `graphics/` owns Vulkan resources and rendering behavior.
- `math/` owns dependency-light math utilities.
- `shaders/` contains source GLSL; CMake compiles it to SPIR-V.
- `docs/` contains design notes, style guidance, and extension ideas.

## Error Handling

- All Vulkan calls that return `VkResult` go through `VulkanRenderer::check`.
- SDL failures include `SDL_GetError()` in the exception message.
- File loading errors include the path that failed.

## Comments

Comments should explain ownership, ordering, or Vulkan-specific pitfalls. Avoid comments that merely restate the next line of code.

Good:

```cpp
// The renderer owns Vulkan objects; the window owns only SDL state.
```

Bad:

```cpp
// Create the buffer.
vkCreateBuffer(...);
```

## Vulkan Conventions

- Create and destroy resources in a predictable order.
- Treat swapchain resources as a separate lifetime group.
- Keep per-frame resources indexed by `currentFrame_`.
- Keep per-image resources indexed by `imageIndex`.
- Use validation layers in Debug builds.
