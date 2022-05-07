#ifndef OGRE_H
#define OGRE_H


class Ogre
{
public:
    Ogre(int a, int b);

    void talk();
    int getHealth() const;
    int getStrength() const;

    void setHealth(int value);
    void setStrength(int value);

private:
    int health;
    int strength;

};

#endif // OGRE_H
