#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using json = nlohmann::json;
using namespace ftxui;

std::vector<int> LoadXPHistory() {
    std::vector<int> xp_list;
    std::ifstream file("dev_history.json");

    if (!file.is_open()) {
        std::cerr << "Could not open dev_history.json file\n";
        return xp_list;
    }

    json data;
    file >> data;

    if (!data.contains("history"))
        return xp_list;

    for (auto& entry : data["history"])
        xp_list.push_back(entry["xp"]);

    if (xp_list.size() > 30)
        xp_list.erase(xp_list.begin(), xp_list.end() - 30);

    return xp_list;
}

int LevelFromXP(int xp) {
    return xp / 100 + 1;
}

int main() {
    auto xp_history = LoadXPHistory();
    if (xp_history.empty()) {
        std::cout << "No XP data found.\n";
        return 0;
    }

    int latest_xp = xp_history.back();
    int level = LevelFromXP(latest_xp);

    Element graph_element = canvas([&](Canvas& c) {
        int w = c.width();
        int h = c.height();

        int max_xp = *std::max_element(xp_history.begin(), xp_history.end());
        int min_xp = *std::min_element(xp_history.begin(), xp_history.end());
        if (max_xp == min_xp)
            max_xp += 1;

        int n = xp_history.size();

        for (int x = 0; x < w; ++x) {
            int idx = x * n / w;
            int xp = xp_history[idx];

            float norm = float(xp - min_xp) / float(max_xp - min_xp);
            int y = h - 1 - int(norm * (h - 1));

            c.DrawPoint(x, y, Color::Yellow);
        }
    }) | border;

    Element header = hbox(Elements{
        text("Level: " + std::to_string(level)) | bold,
        filler(),
        text("Total XP: " + std::to_string(latest_xp)) | bold
    });

    Element document =
        vbox(Elements{
            text("XP Progress - Last 30 Days") | center | bold,
            separator(),
            header,
            separator(),
            graph_element
        }) | border;

    auto screen = Screen::Create(Dimension::Full());
    Render(screen, document);
    screen.Print();
}

