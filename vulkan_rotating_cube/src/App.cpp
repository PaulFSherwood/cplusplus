#include "App.hpp"

#include "graphics/VulkanRenderer.hpp"
#include "platform/SdlWindow.hpp"

#include <SDL2/SDL.h>

#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <unistd.h>

namespace {

[[nodiscard]] std::filesystem::path executableDirectory() {
    std::array<char, 4096> buffer{};

    const ssize_t count = readlink("/proc/self/exe", buffer.data(), buffer.size() - 1U);
    if (count <= 0) {
        return std::filesystem::current_path();
    }

    buffer[static_cast<std::size_t>(count)] = '\0';
    return std::filesystem::path{buffer.data()}.parent_path();
}

} // namespace

namespace cube {

int App::run(int /*argc*/, char** /*argv*/) {
    const auto runtimeDirectory = executableDirectory();
    const auto shaderDirectory = runtimeDirectory / "shaders";
    const auto modelPath = runtimeDirectory / "assets" / "models" / "BRDM.glb";

    SdlWindow window{"Vulkan Krait Phantom", 1280, 720};
    VulkanRenderer renderer{window, shaderDirectory, modelPath};

    const auto start = std::chrono::steady_clock::now();

    // FPS is sampled over a short window instead of every frame. This keeps the
    // title readable and avoids spamming the platform windowing layer.
    auto fpsSampleStart = start;
    std::uint32_t framesInSample = 0;

    bool running = true;

    while (running) {
        SDL_Event event{};
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                renderer.notifyFramebufferResized();
            }
        }

        const auto frameStart = std::chrono::steady_clock::now();
        const float seconds = std::chrono::duration<float>(frameStart - start).count();
        renderer.drawFrame(seconds);

        ++framesInSample;
        const auto frameEnd = std::chrono::steady_clock::now();
        const float sampleSeconds =
            std::chrono::duration<float>(frameEnd - fpsSampleStart).count();

        if (sampleSeconds >= 0.5F) {
            const float fps = static_cast<float>(framesInSample) / sampleSeconds;

            std::ostringstream title;
            title << "Vulkan Krait Phantom | FPS: " << std::fixed
                  << std::setprecision(1) << fps;
            window.setTitle(title.str());

            fpsSampleStart = frameEnd;
            framesInSample = 0;
        }
    }

    renderer.waitIdle();
    return 0;
}

} // namespace cube
