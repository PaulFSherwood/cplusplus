#include "player.h"

Player::Player(int a, int b)
{
    health = a;
    experiance = b;
}

int Player::getHealth() const
{
    return health;
}
int Player::getExperiance() const
{
    return experiance;
}

void Player::setHealth(int value)
{
    health = value;
}
void Player::setExperiance(int value)
{
    experiance = value;
}
