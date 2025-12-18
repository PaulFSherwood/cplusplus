#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

int main() {
   using namespace ftxui;

   // Define the document
   Element document =
      vbox({
            text("FTXUI Example") | bold | hcenter,
            separator(),
            hbox ({
                  text("left")    | border,
                  text("middle")  | border | flex,
                  text("right")   | border,
                  }),
            gauge(0.5) | color(Color::Red),
            });

   // Create a screen
   auto screen = Screen::Create(
         Dimension::Full(),
         Dimension::Fit(document)
         );

   // Render the document to the screen
   Render(screen, document);

   // Print the screen to the terminal
   screen.Print();

   return 0;
}
