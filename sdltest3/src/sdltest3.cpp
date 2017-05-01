//============================================================================
// Name        : sdltest3.cpp
// Author      : paul
// Version     : lazyfoo.net lesson05
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

// header files
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
using namespace std;

// screen atributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// the surfaces
SDL_Surface *background = NULL;
SDL_Surface *foo = NULL;	// this will be the stick man.
SDL_Surface *screen = NULL;

// the even structure
SDL_Event event;

// surface loading
SDL_Surface *load_image(string filename)
{
	// the image that's loaded
	SDL_Surface* loadedImage = NULL;

	// the optimized image that will be used
	SDL_Surface *optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	// if the image loaded
	if (loadedImage != NULL)
	{
		// create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		// free the old image
		SDL_FreeSurface(loadedImage);

		// If the image was optimiezed just fine
		if (optimizedImage != NULL)
		{
			// Map the color key
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);

			// set all pixels of color r 0, g 0xFF, b 0xFF to be transparent
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}
	// return the optimized image
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	// temp rectangle to hold the offsets
	SDL_Rect offset;

	// Get the offsets
	offset.x = x;
	offset.y = y;

	// blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

bool init()
{
	// init all SDL_subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}

	// set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// If there was an error in setting up the screen
	if(screen == NULL)
	{
		return 1;
	}

	// set the winow caption
	SDL_WM_SetCaption("Foo says \"Hello!\"", NULL);

	// If everthing initializedfine
	return true;
}

bool load_files()
{
	// Load the background image
	background = load_image("background.png");

	// if the background didn't load
	if (background == NULL)
	{
		return false;
	}

	// load the stick figure
	foo = load_image("foo.png");

	// if the stick figure didn't load
	if (foo == NULL)
	{
		return false;
	}
	return true;
}

void clean_up()
{
	// Free the surfaces
	SDL_FreeSurface(background);
	SDL_FreeSurface(foo);

	//Quit SDL
	SDL_Quit();
}

int main(int argc, char *args[])
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Apply the surfaces to the screen
    apply_surface( 0, 0, background, screen );
    apply_surface( 240, 190, foo, screen );

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }

    //Free the surfaces and quit SDL
    clean_up();

    return 0;
}
