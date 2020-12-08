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


        void SetHpCap(int hpCap);
        void SetHpCurrent(int hpCurrent);
        
        void SetWeapon(int wep);
        void SetArmor(int armor);

        void SetAtk(int atk);
        void SetDef(int def);
        //////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        int GetHpCap();
        int GetHpCurrent();
        int GetLvl();

        int GetWeapon();
        int GetArmor();

        int GetAtk();
        int GetDef();

        void PrintStats();


    private:
        /* data */
        int Agility;
        int Strength;
        int Stamina;
        int Level;

        int HpCap;
        int HpCurrent;

        int Weapon;
        int Armor;

        int Atk;
        int Def;

};

#endif /* WARRIOR_H_ */