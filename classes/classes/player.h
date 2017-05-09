#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player(int a, int b);

    int getHealth() const;
    int getExperiance() const;

    void setHealth(int value);
    void setExperiance(int value);

private:
    int health;
    int experiance;
};

#endif // PLAYER_H
