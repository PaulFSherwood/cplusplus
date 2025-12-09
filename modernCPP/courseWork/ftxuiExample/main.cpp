#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>

using namespace ftxui;

struct Player {
   int hp = 100;
   int mana = 50;
   int gold = 20;
};

int main() {
   auto screen = ScreenInteractive::Fullscreen();
   Player player;

   // --- Game States --- // 
   enum class MenuPage { Main, Stats, Forest, Bank };
   MenuPage current_page = MenuPage::Main;

   // --- Callback Handlers --- // 
   auto go_to_main   = [&]{ current_page = MenuPage::Main; };
   auto go_to_stats  = [&]{ current_page = MenuPage::Stats; };
   auto go_to_forest = [&]{ current_page = MenuPage::Forest; };
   auto go_to_bank   = [&]{ current_page = MenuPage::Bank; };

   // --- Buttons --- // 
   Component forest_btn = Button("Go to Forest", go_to_forest);
   Component bank_btn   = Button("Visit Bank", go_to_bank);
   Component stats_btn  = Button("Your Stats", go_to_stats);
   Component back_btn   = Button("Back", go_to_main);

   // --- Container to allow keyboard navigation
   auto menu_container = Container::Vertical({
         forest_btn,
         bank_btn,
         stats_btn,
         bank_btn
   });

   // --- Main Renderer --- // 
   Component renderer = Renderer(menu_container, [&] {
         Element main_menu = vbox({
               text("=== Welcome to Tiny FTXUI RPG ===") | bold | center,
               separator(),
               forest_btn->Render(),
               bank_btn->Render(),
               stats_btn->Render(),
               separator(),
               }) | border | center;
         Element stats_page = vbox({
               text("=== Your Stats ===") | bold | center,
               separator(),
               hbox(text("HP:   ") | bold, text(std::to_string(player.hp))),
               hbox(text("Mana: ") | bold, text(std::to_string(player.mana))),
               hbox(text("Gold: ") | bold, text(std::to_string(player.gold))),
               separator(),
               back_btn->Render(),
               }) | border | center;
         Element forest_page = vbox({
               text("=== Forest ===") | bold | center,
               separator(),
               text("You wandered into the forest.") | center,
               text("Nothing happened... yet.") | center,
               separator(),
               back_btn->Render(),
               }) | border | center;
         Element bank_page = vbox({
               text("=== Bank ===") | bold | center,
               separator(),
               text("The bank is quiet today.") | center,
               text("You check your account balanace.") | center,
               separator(),
               back_btn->Render(),
               }) | border | center;

         // --- Page Switcher --- // 
         switch(current_page) {
            case MenuPage::Main:    return main_menu;
            case MenuPage::Stats:   return stats_page;
            case MenuPage::Forest:  return forest_page;
            case MenuPage::Bank:    return bank_page;
         }
         return main_menu;
         });

   screen.Loop(renderer);
   return 0;
}
