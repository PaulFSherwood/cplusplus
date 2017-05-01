// headers
#include "SDL/SDL.h"
#include <iostream>

int main(int argc, char* args[])
{
	// init surfaces
	SDL_Surface *hello = NULL;
	SDL_Surface *screen = NULL;

	// start sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	// Set up the screen
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

	// load image
	hello = SDL_LoadBMP("hello.bmp");

	// apply image to the screen
	SDL_BlitSurface(hello, NULL, screen, NULL);

	// Update the screen
	SDL_Flip(screen);

	// pause
	SDL_Delay(2000);

	// Free the loaded image
	SDL_FreeSurface(hello);

	// quit sdl
	SDL_Quit();
}
