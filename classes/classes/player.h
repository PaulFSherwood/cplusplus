#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player(int a, int b, int c);

    int getHealth() const;
    int getExperiance() const;
    int getStrength() const;

    void setHealth(int value);
    void setExperiance(int value);
    void setStrength(int value);

private:
    int health;
    int strength;
    int experiance;
};

#endif // PLAYER_H
