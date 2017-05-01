#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

void drawSprite(SDL_Surface* imageSurface,
                SDL_Surface* screenSurface,
                int srcX, int srcY,
                int dstX, int dstY,
                int width, int height);

int main(int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO );

	SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	SDL_Surface* bitmap = SDL_LoadBMP("bat.bmp");
	SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format, 255, 0, 255));

	int batImageX = 24;
	int batImageY = 63;
	int batWidth = 65;
	int batHeight = 44;

	// We change these to make the bat move
	int batX = 100;
	int batY = 100;

	SDL_Event event;
	bool gameRunning = true;

	bool keysHeld[323] = {false}; // everything will be initialized to false

	while (gameRunning)
	{
		// Handle input
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}

			if (event.type == SDL_KEYDOWN)
			{
				keysHeld[event.key.keysym.sym] = true;
			}
			if (event.type == SDL_KEYUP)
			{
				keysHeld[event.key.keysym.sym] = false;
			}
		}
		if ( keysHeld[SDLK_ESCAPE] )
		{
			gameRunning = false;
		}

		if ( keysHeld[SDLK_LEFT] )
		{
			batX -= 3;
		}
		if ( keysHeld[SDLK_RIGHT] )
		{
			batX += 3;
		}
		if ( keysHeld[SDLK_UP] )
		{
			batY -= 3;
		}
		if (keysHeld[SDLK_DOWN])
		{
			batY += 3;
		}

		// Draw the scene
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		drawSprite(bitmap, screen, batImageX, batImageY, 	batX, batY, batWidth, batHeight);

		SDL_Flip(screen);
	}

	SDL_FreeSurface(bitmap);

	SDL_Quit();

	return 0;
}

void drawSprite(SDL_Surface* imageSurface,
                SDL_Surface* screenSurface,
                int srcX, int srcY,
                int dstX, int dstY,
                int width, int height)
{
	SDL_Rect srcRect;
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = width;
	srcRect.h = height;

	SDL_Rect dstRect;
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = width;
	dstRect.h = height;

	SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
}
