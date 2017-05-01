//headers
#include "SDL/SDL.h"
#include <string>

// the attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;
const int SCREEN_BPP = 32;

// the surface that will be used
SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

// image loading function
SDL_Surface *load_image(std::string filename)
{
	// temporary storage for the image thats loaded
	SDL_Surface *loadedImage = NULL;
	// the optimized image
	SDL_Surface *optimizedImage = NULL;
	
	// load the image
	loadedImage = SDL_LoadBMP(filename.c_str());
	
	// if nothing went wrong in loading the image
	if(loadedImage != NULL)
	{
		// create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);
		
		//free the old image
		SDL_FreeSurface(loadedImage);
	}
	// return the optimized image
	return optimizedImage;
}

// surface blitting
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	// make a temporary rectangle  to hold the offsets
	SDL_Rect offset;
	
	// give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	//blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

// main function
int main(int argc, char *args[])
{
	// init sdl sybsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}
	
	// set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	// if there was an error in setting up the screen
	if(screen == NULL)
	{
		return 1;
	}
	
	// set the window caption
	SDL_WM_SetCaption("hello world", NULL);
	
	// load the images
	message = load_image( "hello.bmp" );
    	background = load_image( "background.bmp" );
    	
	
	// apply the background to the screen
	apply_surface(0, 0, background, screen);
	apply_surface(320, 0, background, screen);	
	apply_surface(0, 240, background, screen);
	apply_surface(320, 240, background, screen);
	
	// apply the message to the screen
	apply_surface(180, 140, message, screen);
	
	// update the screen
	if(SDL_Flip(screen) == -1)
	{
		return 1;
	}
	
	// wait 2 seconds
	SDL_Delay(2000);
	
	// free the surface
	SDL_FreeSurface(message);
	SDL_FreeSurface(background);
	
	// Quit SDL
	SDL_Quit();
	
	// return 
	return 0;
}
