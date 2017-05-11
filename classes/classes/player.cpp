#include "player.h"

Player::Player(int a, int b, int c)
{
    health = a;
    tempHealth = a;
    strength = b;
    experiance = c;
}

int Player::getHealth() const
{
    return health;
}
int Player::getTempHealth() const
{
    return tempHealth;
}
int Player::getExperiance() const
{
    return experiance;
}

void Player::setHealth(int value)
{
    health = value;
}
void Player::setTempHealth(int value)
{
    tempHealth = value;
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
