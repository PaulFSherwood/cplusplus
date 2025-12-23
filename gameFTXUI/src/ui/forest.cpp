#include "forest.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

ftxui::Component ForestMenu(GameScreen &current_screen) {
    auto renderer = Renderer([&] {
        return vbox({
                text("== The Forest ==") | bold,
                separator(),
                text("[V] Return to the Village"),
            }) | border;
        });

    return CatchEvent(renderer, [&](Event event) {
        if (event == Event::Character('v')) {
            current_screen = GameScreen::Village;
            return true;
        }
        return false;
    });
}
