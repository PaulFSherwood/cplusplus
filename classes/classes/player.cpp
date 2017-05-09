#include "player.h"

Player::Player(int a, int b, int c)
{
    health = a;
    strength = b;
    experiance = c;
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

int Player::getStrength() const
{
    return strength;
}

void Player::setStrength(int value)
{
    strength = value;
}
