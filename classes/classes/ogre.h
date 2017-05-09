#ifndef OGRE_H
#define OGRE_H


class Ogre
{
public:
    Ogre();

    void talk();
    int getHealth() const;
    void setHealth(int value);

private:
    int health;
    int strength;

};

#endif // OGRE_H
