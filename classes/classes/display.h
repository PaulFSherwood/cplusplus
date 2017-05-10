#ifndef DISPLAY_H
#define DISPLAY_H
#include "ogre.h"
#include "player.h"

class Display
{
public:
    void showScene(Player * dude);
    void showFight(Player * dude);
    Display();
};

#endif // DISPLAY_H
