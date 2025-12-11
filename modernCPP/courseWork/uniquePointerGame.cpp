#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ----------
// Player
// ----------
class Player {
   public:
      Player(std::string name)
         : name_(std::move(name)), hp_(100), gold_(10) {}
      
      void showStats() const {
         std::cout << "\n=== Stats ===\n";
         std::cout << "Name: " << name_ << "\n";
         std::cout << "HP:   " << hp_ << "\n";
         std::cout << "Gold: " << gold_ << "\n";
      }

      void addGold(int amount) { gold_ += amount; }
      void hurt(int amount) { hp_ -= amount; if (hp_ < 0) hp_ = 0; }
      bool isAlive() const { return hp_ > 0; }

   private:
      std::string name_;
      int hp_;
      int gold_;
};

// ----------
// Base Location
// ----------
class Location {
   public:
      virtual ~Location() = default;
      virtual void enter(Player& player) = 0;
};

// ----------
// Forest (fight or find gold) 
// ----------
class Forest : public Location {
   public:
      void enter(Player& player) override {
         std::cout << "\nYou enter the forest...\n";
         int event = rand() % 2;
         if (event == 0) {
            std::cout << "A wild goblin attacks! You loos 5 HP.\n";
            player.hurt(5);
         } else {
            std::cout << "You find 10 gold lying on a stump.\n";
            player.addGold(10);
         }
      }
};

// ----------
// Bank 
// ----------
class Bank : public Location {
   public:
      void enter(Player& player) override {
         std::cout << "\nYou visit the bank.\n";
         std::cout << "But there is nothing implemented yet.\n";
      }
};

// ----------
// Game class that OWNS locations via unique_ptr 
// ----------
class Game {
   public:
      Game(std::unique_ptr<Player> player)
         : player_(std::move(player))   // <-- move semantics
      {
         // make_unique cannot be copied, but can be moved
         locations_.push_back(std::make_unique<Forest>());
         locations_.push_back(std::make_unique<Bank>());
      }

      void mainLoop() {
         while (player_->isAlive()) {
            std::cout << "\n--- Village Center ---\n";
            std::cout << "1. Go to the Forest\n";
            std::cout << "2. Go to the Bank\n";
            std::cout << "3. View Stats\n";
            std::cout << "0. Quit\n";
            std::cout << "Choice: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
               case 1:
                  locations_[0]->enter(*player_);
                  break;
               case 2:
                  locations_[1]->enter(*player_);
                  break;
               case 3:
                  player_->showStats();
                  break;
               case 0:
                  return;
               default:
                  std::cout << "Invalid choice.\n";
                  break;
                  break;
            }
         }
         std::cout << "\nYou have fallin in battle...\n";
      }
   private:
      std::unique_ptr<Player> player_;                    // Owns the player 
      std::vector<std::unique_ptr<Location>> locations_;  // Owns locations
};

// -----------
// main
// -----------
int main() {
   std::srand(static_cast<unsigned>(time(nullptr)));

   std::cout << "Enter your name: ";
   std::string name;
   std::getline(std::cin, name);

   std::unique_ptr<Player> p = std::make_unique<Player>(std::move(name));

   Game game(std::move(p));   // transfer ownder ship of player to game 

   game.mainLoop();

   return 0;
} 
