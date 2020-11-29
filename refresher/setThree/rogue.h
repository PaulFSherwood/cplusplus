#ifndef ROGUE_H_
#define ROGUE_H_

class Rogue
{
    public:
        Rogue(int startLevel);   // I guess this will end up in the .h files
        ~Rogue();
        // ============================
        int getAgility();
        int getStrength();
        int getStamina();
        int getLevel();
        // ============================
        void setAgility (int LEVEL);
        void setStrength(int LEVEL);
        void setStamina (int LEVEL);
        void setLevel   (int LEVEL);

    private:
        /* data */
        int Agility;
        int Strength;
        int Stamina;
        int Level;
};

#endif /* ROGUE_H_ */