#include "platform/SdlWindow.hpp"

#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <stdexcept>
#include <string>
#include <string_view>

namespace cube {

SdlWindow::SdlWindow(std::string title, std::int32_t width, std::int32_t height) {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error{"SDL_Init failed: " + std::string{SDL_GetError()}};
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    if (window_ == nullptr) {
        const std::string message = SDL_GetError();
        SDL_Quit();
        throw std::runtime_error{"SDL_CreateWindow failed: " + message};
    }
}

SdlWindow::~SdlWindow() {
    if (window_ != nullptr) {
        SDL_DestroyWindow(window_);
    }
    SDL_Quit();
}

void SdlWindow::setTitle(std::string_view title) const {
    SDL_SetWindowTitle(window_, std::string{title}.c_str());
}

VkExtent2D SdlWindow::drawableExtent() const {
    int width = 0;
    int height = 0;
    SDL_Vulkan_GetDrawableSize(window_, &width, &height);

    return VkExtent2D{
        .width = static_cast<std::uint32_t>(width),
        .height = static_cast<std::uint32_t>(height)};
}

} // namespace cube
