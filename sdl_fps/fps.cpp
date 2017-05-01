#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen;
	screen=SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	bool running = true;
	const int FPS = 30;
	Uint32 start;
	while(running)
	{
		start = SDL_GetTicks();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
			}
		}
		SDL_Flip(screen);
	
		 if(1000/FPS>SDL_GetTicks() - start)
		 SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		 
	}
	SDL_Quit();
	return 0;
}

