#ifndef WARRIOR_H_
#define WARRIOR_H_

class Warrior
{
    public:
        Warrior(int startLevel);   // I guess this will end up in the .h files
        ~Warrior();
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

#endif /* WARRIOR_H_ */