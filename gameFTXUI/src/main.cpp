// src/main.cpp
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

#include "game_screen.hpp"
#include "ui/village.hpp"
#include "ui/forest.hpp"

using namespace ftxui;

int main() {
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();

    GameScreen current_screen = GameScreen::Village;

    // We will swap this component based on state
    Component app;

    auto render = [&]() -> Component {
        if (current_screen == GameScreen::Village)
            return VillageMenu(current_screen);
        else
            return ForestMenu(current_screen);
    };

    app = Renderer([&] {
        return render()->Render();
    });

    screen.Loop(app);
    return 0;
}

