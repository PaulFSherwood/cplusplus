#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player(int a, int b, int c);

    int getHealth() const;
    int getTempHealth() const;
    int getExperiance() const;
    int getStrength() const;

    void setHealth(int value);
    void setTempHealth(int value);
    void setExperiance(int value);
    void setStrength(int value);

private:
    int health;
    int tempHealth;
    int strength;
    int experiance;
};

#endif // PLAYER_H
