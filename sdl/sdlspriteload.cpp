#include "SDL/SDL.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

void drawSprite(SDL_Surface*	imageSurface,	/* bitmap 1 */
		SDL_Surface*	screenSurface,	/* screen 3*/
		int srcX,	int srcY,
		int dstX,	int dstY,
		int srcwidth,	int srcheight,
		int dstwidth,	int dstheight)
{
	SDL_Rect srcRect;			/* pic area to use 2 */
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = srcwidth;
	srcRect.h = srcheight;

	SDL_Rect dstRect;			/* screen area to put it 4 */
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = dstwidth;
	dstRect.h = dstheight;
			/*1*/		/*2*/	/*3*/		/*4*/
	SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
}


int main()
{
/*3*/	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption ( WINDOW_TITLE, 0);

	// clear the screen
	// what surface to clear | null clear everything | what color to change to
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	// to load a bitmap file
/*1*/	SDL_Surface* bitmap = SDL_LoadBMP("bat.bmp");

	// Set color to be transparent
      //SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 255, 0, 255));
	SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format, 255, 0, 255));

	// Part of the bitmap that we want to draw
/*2*///	SDL_Rect source;
/*	source.x = 24;
	source.y = 63;
	source.w = 65;
	source.h = 44;
*/
	// Part of the screen we want to draw the sprite to
/*4*///	SDL_Rect destination;
/*	destination.x = 100;
	destination.y = 100;
	destination.w = 65;
	destination.h = 44;
*/	

	SDL_Event event;
	bool gameRunning = true;

	while(gameRunning)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}
		// drawing by function
		drawSprite(bitmap, screen, 24,63, 100, 100, 65, 44, 65, 44);
		// To draw the bitmap use this, take 4 parameters
		// SDL_BlitSurface(bitmap, &source, screen, &destination);

		SDL_Flip(screen);
	}

	SDL_FreeSurface(bitmap);

	SDL_Quit();

	return 0;
}
