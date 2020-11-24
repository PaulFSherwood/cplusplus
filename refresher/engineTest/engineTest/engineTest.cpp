// engineTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class WarpedDungeon : public olc::PixelGameEngine
{
public:
	WarpedDungeon()
	{
		sAppName = "Warped Dungeon";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		return true;
	}
};


int main()
{
	WarpedDungeon demo;
	if (demo.Construct(640, 480, 2, 2, false))
		demo.Start();

	return 0;
}