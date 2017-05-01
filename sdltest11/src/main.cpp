#include "SDL/SDL.h"
#include <iostream>

int main(int argc, char *args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	std::cout << "SDL is running\n";

	SDL_Quit();

}
