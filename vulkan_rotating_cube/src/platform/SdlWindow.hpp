#pragma once

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

#include <cstdint>
#include <string>
#include <string_view>

namespace cube {

// RAII wrapper around the SDL video subsystem and the native window.
// The renderer owns Vulkan objects; this class owns only SDL state.
class SdlWindow final {
public:
    SdlWindow(std::string title, std::int32_t width, std::int32_t height);
    ~SdlWindow();

    SdlWindow(const SdlWindow&) = delete;
    SdlWindow& operator=(const SdlWindow&) = delete;
    SdlWindow(SdlWindow&&) = delete;
    SdlWindow& operator=(SdlWindow&&) = delete;

    [[nodiscard]] SDL_Window* nativeHandle() const noexcept { return window_; }
    [[nodiscard]] VkExtent2D drawableExtent() const;

    // UI-only helper used by the application layer for diagnostics such as FPS.
    // Vulkan rendering state does not depend on the window title.
    void setTitle(std::string_view title) const;

private:
    SDL_Window* window_{nullptr};
};

} // namespace cube
