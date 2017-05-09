#ifndef OGRE_H
#define OGRE_H


class Ogre
{
public:
    int health;
    int strength;

    void talk();

    int getHealth() const;
    void setHealth(int value);

    Ogre();
};

#endif // OGRE_H
