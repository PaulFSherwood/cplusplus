#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// AX			 , AY              , AW          , AH         |||, BX              , BY               , BW            , BH
//padImageX, padImageY, padWidth, padHeight, ball_imageX, ball_imageY, ball_Width, ball_Height
bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
  if ( Ay + Ah < By ) return false;
  else if ( Ay > By + Bh ) return false;
  else if ( Ax + Aw < Bx ) return false;
  else if ( Ax > Bx + Bw ) return false;
  return true;
}

void drawText(SDL_Surface *screen,
		char *string,
		int size,
		int x, int y,
		int fR, int fG, int fB,
		int bR, int bG, int bB);

char mystring[128];

void txtIt(char *pStr, ...);

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Pong";

void drawSprite(SDL_Surface* imageSurface,
                SDL_Surface* screenSurface,
                int srcX, int srcY,
                int dstX, int dstY,
                int width, int height);
/*
void drawText(SDL_Surface* screen,
        char* string,
        int size,
        SDL_Rect textLocation,
        SDL_Color foregroundColor,
        SDL_Color backgroundColor);
*/
int main(int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO );

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("lazy.ttf", 24);
	TTF_Init();

	SDL_Surface *imgTxt;
	SDL_Rect txtRect = {94,35};
	SDL_Rect txtRect2 = {410,35};
	SDL_Color fColor = {245,245, 245};

	// score chart
	int p1Score = 0;
	int cpuScore = 0;

	atexit(SDL_Quit);

	SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	SDL_Surface* bitmap = SDL_LoadBMP("pad.bmp");
	SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format, 255, 0, 255));

	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Color backgroundColor = { 0, 0, 0 };

	SDL_Surface* PlayertextSurface = TTF_RenderText_Shaded(font, "Player", foregroundColor, backgroundColor);
	SDL_Surface* ComptextSurface = TTF_RenderText_Shaded(font, "Computer", foregroundColor, backgroundColor);

	// Pass zero for width and height to draw the whole surface
	SDL_Rect PlayertextLocation = { 100, 10, 0, 0 };
	SDL_Rect ComptextLocation = { 400, 10, 0, 0 };

	int padImageX = 25;
	int padImageY = 25;
	int padWidth = 25;
	int padHeight = 75;

	// We change these to make the pad move
	float padX = 10;
	float padY = 200;

	// ball image
	int ball_imageX = 75;
	int ball_imageY = 25;
	int ball_Width = 25;
	int ball_Height = 25;

	// we change these to make the ball move
	float ballX = 320;
	float ballY = 240;
	float vellX = 1;
	float vellY = -3;

	// cpu pad
	int cpupadImageX = 25;
	int cpupadImageY = 25;
	int cpupadWidth = 25;
	int cpupadHeight = 75;

	// cpu you change x/y var
	float cpupadX = 600;
	float cpupadY = 200;

	SDL_Event event;
	bool gameRunning = true;

	// key states
	bool up = false, down = false;

	while (gameRunning)
	{
		// Handle input
		if (SDL_PollEvent(&event))
		{
			// quit key action
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			else if(event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameRunning = false;
			}
			// key input action
			if (event.type == SDL_KEYDOWN)
			{
				if ( event.key.keysym.sym == SDLK_UP )
				{
					up = true;
				}
				else if ( event.key.keysym.sym == SDLK_DOWN )
				{
					down = true;
				}
			}
			else if ( event.type == SDL_KEYUP )
			{
				if ( event.key.keysym.sym == SDLK_UP )
				{
					up = false;
				}
				else if ( event.key.keysym.sym == SDLK_DOWN )
				{
					down = false;
				}
			}
		}

		// PAD LOGIC
		if (up == true)
		{
			padY -= 3;
		}
		if (down == true)
		{
			padY += 3;
		}
		// collision
		if (padY < 0)
		{
			padY = 0;
		}
		if (padY > WINDOW_HEIGHT- padHeight)
		{
			padY = WINDOW_HEIGHT - padHeight;
		}

		// cpu Pad Logic
		if ((ballY + (ball_Height/2)) > (cpupadY+(cpupadHeight/2)))
		{
			cpupadY += .5;
		}
		if ((ballY + (ball_Height/2)) < (cpupadY+(cpupadHeight/2)))
		{
			cpupadY -= .5;
		}
		// cpu pad wall collision
		if (cpupadY < 0)
		{
			cpupadY = 0;
		}
		if (cpupadY > WINDOW_HEIGHT- cpupadHeight)
		{
			cpupadY = WINDOW_HEIGHT - cpupadHeight;
		}
		// CPU pad collision check
		if ( checkCollision( cpupadX, cpupadY, cpupadWidth, cpupadHeight, ballX, ballY, ball_Width, ball_Height ) == true )
		{
		  vellX = -vellX;
		}

		// moving the ball
		ballX = ballX + (vellX/2);
		ballY = ballY + (vellY/5);

		// Ball Logic

		if (ballX < 0)
		{// bottom side of screen (bottom)
			cout << "Left Side" << endl;

			padX = 10;
			padY = 200;

			ballX = 320;
			ballY = 240;

			cpupadX = 600;
			cpupadY = 200;

			cpuScore +=1;

			SDL_Delay(1000);
		}
		else if ( (ballX+ball_Width) > 640 )
		{
			cout << "Right Side" << endl;

			padX = 10;
			padY = 200;

			ballX = 320;
			ballY = 240;

			cpupadX = 600;
			cpupadY = 200;

			p1Score +=1;

			SDL_Delay(1000);
		}
		if ( ballY < 0 )
		{
			vellY = -vellY;
		}
		else if ( ballY+ball_Height > 480 )
		{
			vellY = -vellY;
		}
		if ( checkCollision( padX, padY, padWidth, padHeight, ballX, ballY, ball_Width, ball_Height ) == true )
		{ // this is an attempt to get some reall action out of the ball
			// its supposed to go down if it hits the right side of the pad and up if it hits the left.
			if ( (ballY + (ball_Height/2)) > (padY+(padHeight/2)) )
			{
				cout << "ball: " <<  (ballY + (ball_Height/2)) << "pad: " << (padY+(padHeight/2)) << endl;
				vellY = -vellY;
			}
			if ( (ballY + (ball_Height/2)) < (padY+(padHeight/2)) )
			{
				cout << "2ball: " <<  (ballY + (ball_Height/2)) << "2pad: " << (padY+(padHeight/2)) << endl;
				vellY = -vellY;
			}
		  vellX = -vellX;
		}

		// Draw the scene
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		SDL_BlitSurface(PlayertextSurface, NULL, screen, &PlayertextLocation);

		SDL_BlitSurface(ComptextSurface, NULL, screen, &ComptextLocation);

		txtIt("%4d", p1Score);
		imgTxt = TTF_RenderText_Solid(font, mystring, fColor);
		SDL_BlitSurface(imgTxt, NULL, screen, &txtRect);

		txtIt("%4d", cpuScore);
		imgTxt = TTF_RenderText_Solid(font, mystring, fColor);
		SDL_BlitSurface(imgTxt, NULL, screen, &txtRect2);

		//int num = 234;

		//txtIt("%4d", num);
						     //TEXT/////BACKGROUND
		//drawText(screen, mystring, 12, 30, 30, 245, 245, 245, 0, 0, 0);

		drawSprite(bitmap, screen, padImageX, padImageY, padX, padY, padWidth, padHeight);

		drawSprite(bitmap, screen, ball_imageX, ball_imageY, ballX, ballY, ball_Width, ball_Height);

		drawSprite(bitmap, screen, cpupadImageX, cpupadImageY, cpupadX, cpupadY, cpupadWidth, cpupadHeight);

		SDL_Flip(screen);
	}

	SDL_FreeSurface(bitmap);
	SDL_FreeSurface(PlayertextSurface);
	SDL_FreeSurface(ComptextSurface);
	SDL_FreeSurface(imgTxt);

	TTF_Quit();

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
