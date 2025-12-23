#include "village.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

ftxui::Component VillageMenu(GameScreen & current_screen) {
    auto renderer = Renderer([&] {
            return vbox({
                    text("== Village Gate ==") | bold,
                    separator(),
                    text("[F] Enter the Forest"),
                    text("[Q] Quit"),
                    }) | border;
            });

    return CatchEvent(renderer, [&](Event event) {
        if (event == Event::Character('f')) {
            current_screen = GameScreen::Forest;
            return true;
        }
        if (event == Event::Character('q')) {
            exit(0);
        }
        return false;
    });
}
