struct Character {
   int x;
   int y;
};

class Command {
   public:
      virtual ~Command() {}
      virtual void execute(Character& c) = 0;
      virtual void undo(Character& c) = 0;
};

class Move : public Command {
   public:
      void execute(Character& c) {

      }
      void undo(Character& c) {

      }
};

int main() {
   Move m;

   return 0;
}
