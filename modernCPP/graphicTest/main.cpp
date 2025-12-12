#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <cmath>
#include <chrono>

using namespace ftxui;

double terrain(double x) {
   return std::sin(x * 0.08) 
      + 0.6 * std::sin(x * 0.17) 
      + 0.3 * std::sin(x * 0.31);
}

Element terrain_layer(double t, int width, double speed, char glyph) {
   std::string line;
   for (int x = 0; x < width; ++x) {
      double h = terrain(x + t * speed);
      line += (h > 0.0 ? glyph : ' ');
   }
   return text(line);
}

int main() {
   auto screen = ScreenInteractive::TerminalOutput();

   double time = 0.0;

   screen.Loop(Renderer([&] {
      time += 0.05;

         return vbox({
            text("     |---------- ORBITAL VIEW ----------|"),
            hbox({
               text("   |"),
               vbox({
                  terrain_layer(time, 40, 1.5, '#'),
                  terrain_layer(time, 40, 1.0, '@'),
                  terrain_layer(time, 40, 0.6, '^'),
               }) | border,
            }),
            text("     |----------------------------------|"),
         });
   }));
}
