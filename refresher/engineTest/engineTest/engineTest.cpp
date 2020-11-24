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

	struct sCell
	{
		bool wall = false;
		olc::vi2d id[6]{ };
	};

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		
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