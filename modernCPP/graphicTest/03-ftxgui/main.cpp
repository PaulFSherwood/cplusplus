#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using json = nlohmann::json;
using namespace ftxui;

// ------------------------------------------------
// Load last 30 days of XP from dev_history.json
// ------------------------------------------------
std::vector<int> LoadXPHistory() {
   std::vector<int> xp_list;
   std::ifstream file("dev_history.json");

   if(!file.is_open()) {
      std::cerr << "Could not open dev_history.json file" << std::endl;
      return xp_list;
   }

   json data;
   file >> data;

   if (!data.contains("history")) return xp_list;

   for (auto& entry : data["history"]) {
      xp_list.push_back(entry["xp"]);
   }

   // Only last 30 
   if (xp_list.size() > 30) {
      xp_list.erase(xp_list.begin(), xp_list.end() - 30);
   }
   return xp_list;
}
// ------------------------------------------------
// Convert XP -> Level (simple formula) 
// ------------------------------------------------
int LevelFromXP(int xp) {
   return xp / 100 + 1;
}
// ------------------------------------------------
// Main graph rendering
// ------------------------------------------------
int main() {
   auto xp_history = LoadXPHistory();
   if (xp_history.empty()) {
      std::cout << "No XP data found." << std::endl;
      return 0;
   }

   int latest_xp = xp_history.back();
   int level = LevelFromXP(latest_xp);

   // FTXUI graph requires float values
   std::vector<float> points;
   for (int xp : xp_history) {
      points.push_back((float)xp);
   }
   auto graph_element = graph(std::move(points)) | color(Color::Yellow);

   auto header = hbox({
         text(" Leve: " + std::to_string(level)) | bold,
         filler(),
         text(" Total XP: " + std::to_string(latest_xp)) | bold
         });

   auto document = 
      vbox ({
            text(" XP Progress - Last 30 Days") | center | bold,
            seperator(),
            header,
            seperator(),
            graph_element | border
            }) | border;

   auto screen = Screen::Create(Dimension::Full());
   Render(screen, document);
   screen.Print();

   return 0;
}
