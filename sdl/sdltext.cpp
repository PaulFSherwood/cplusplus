#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

void drawText(SDL_Surface *screen,
		char *string,
		int size,
		int x, int y,
		int fR, int fG, int fB,
		int bR, int bG, int bB);

char mystring[128];

void txtIt(char *pStr, ...);

int main(int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO );

   	TTF_Init();

   	SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
   	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

   	TTF_Font* font = TTF_OpenFont("arial.ttf", 12);

   	SDL_Color foregroundColor = { 255, 255, 255 }; 
   	SDL_Color backgroundColor = { 0, 0, 255 };

   	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "This is my text.", foregroundColor, backgroundColor);

   	// Pass zero for width and height to draw the whole surface 
   	SDL_Rect textLocation = { 100, 100, 0, 0 };

   	SDL_Event event;
	bool gameRunning = true;

   	while (gameRunning)
   	{
      		if (SDL_PollEvent(&event))
     	 	{
         		if (event.type == SDL_QUIT)
         			{
            				gameRunning = false;
         			}
      		}

      		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

      		SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

		int num = 234;

		txtIt("%4d", num);
						     //TEXT/////BACKGROUND
		drawText(screen, mystring, 12, 30, 30, 245, 245, 245, 0, 0, 0);

      		SDL_Flip(screen);
   	}

   	SDL_FreeSurface(textSurface);

   	TTF_CloseFont(font);

   	TTF_Quit();

   	SDL_Quit();
	return 0;
}

void drawText(SDL_Surface *screen, 
		char *string, 
		int size, 
		int x, int y, 
		int fR, int fG, int fB, 
		int bR, int bG, int bB)
{
	TTF_Font *font = TTF_OpenFont("arial.ttf", size);


	SDL_Color foregroundColor = { fR, fG, fB };
	SDL_Color backgroundColor = { bR, bG, bB };

	SDL_Surface *textSurface = TTF_RenderText_Shaded(font, string, foregroundColor, backgroundColor);

	SDL_Rect textLocation = { x, y, 0, 0 };

	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

	SDL_FreeSurface(textSurface);

	TTF_CloseFont(font);
}	

void txtIt(char *pStr, ...)
{// https://sites.google.com/sites/sdlgamer/beginner/lesson-11
	va_list valist;
	va_start(valist, pStr);
	vsprintf(mystring, pStr, valist);
	va_end(valist);
	return;
}
