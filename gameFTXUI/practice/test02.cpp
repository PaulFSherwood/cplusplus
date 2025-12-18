#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>

int main() {
  using namespace ftxui;
  
  // Data
  std::string name;
  
  // Create an input component
  Component input = Input(&name, "Enter your name");
  
  // Add a border and custom rendering
  auto renderer = Renderer(input, [&] {
    return vbox({
      text("Input Example") | bold | hcenter,
      separator(),
      hbox(text("Name: ") | bold | color(Color::Red), input->Render()),
      text("Press Enter when done"),
    }) | border;
  });
  
  // Run the main loop
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
  
  return 0;
}
