/*This source code copyrighted by Lazy Foo' Productions (2004-2011)
and may not be redestributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *dots = NULL;		// the surface that is going to hold the dots that we extract
SDL_Surface *screen = NULL;		// the surface that is going to hold everything

//The event structure
SDL_Event event;			// lets you watch the events like key strokes or if you click X

//The portions of the sprite map to be blitted
SDL_Rect clip[ 4 ];			// variable to hold the dots. X,Y,W,H

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;	// set the loadedImage to null so no issues arise

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;	// set the optimizedImage to null so no issues arise

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );	// now we can load the file and set it to loadedImage

    //If the image loaded
    if( loadedImage != NULL )	// if the image loaded fine continue
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );		// now we optimize the image so its square i think

        //Free the old surface
        SDL_FreeSurface( loadedImage );	// clear the old loadedImage

        //If the surface was optimized
        if( optimizedImage != NULL )	// if the image optimized fine continue
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }	// now we can find and mark the transparent section
    }

    //Return the optimized surface
    return optimizedImage;		// the image is done being modified, now we can send it back to the calling object.
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;	// offset variable hold the demintions of the rectangle i think.

    //Get offsets
    offset.x = x;			// now we can set the x position
    offset.y = y;			// now we can set the y position

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );	// now we can write the image to the destination 
    								// using the offsets of where it should go
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )	// initialize all of sdl for use
    {
        return false;		// if it didnt work say so
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    // tell sdl what the screen will look like (width, height, color depth, were to write to (system mem or video mem)

    //If there was an error in setting up the screen
    if( screen == NULL )	// if the screen is mucked up
    {
        return false;			// if the screen is mucked up say so
    }

    //Set the window caption
    SDL_WM_SetCaption( "Split the dots", NULL ); // Title of the window

    //If everything initialized fine
    return true;			// if everthing so far is good say so.
}

bool load_files()
{
    //Load the sprite map
    dots = load_image( "dots.png" );	// tell sdl what image file to load

    //If there was an problem loading the sprite map
    if( dots == NULL )
    {
        return false;			// if the image failed to load say so
    }

    //If eveything loaded fine
    return true;
}

void clean_up()
{
    //Free the sprite map
    SDL_FreeSurface( dots );		// remove image file from memory

    //Quit SDL
    SDL_Quit();				// stop SDL
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;			// set quit to false so program can run

    //Initialize
    if( init() == false )		// check if init failed or not
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )		// if we couldnt load files stop
    {
        return 1;
    }

    //Clip range for the top left
    clip[ 0 ].x = 0;			// we are picking out where on the png to get the picture
    clip[ 0 ].y = 0;			// you could think of it like croping when you scan a picture
    clip[ 0 ].w = 100;
    clip[ 0 ].h = 100;

    //Clip range for the top right
    clip[ 1 ].x = 100;
    clip[ 1 ].y = 0;
    clip[ 1 ].w = 100;
    clip[ 1 ].h = 100;

    //Clip range for the bottom left
    clip[ 2 ].x = 0;
    clip[ 2 ].y = 100;
    clip[ 2 ].w = 100;
    clip[ 2 ].h = 100;

    //Clip range for the bottom right
    clip[ 3 ].x = 100;
    clip[ 3 ].y = 100;
    clip[ 3 ].w = 100;
    clip[ 3 ].h = 100;

    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    // set the background color to white

    //Apply the sprites to the screen
    int a=0,b=1,c=2,d=3;

    for (int x = 0; x < 10; x++)
    {
    	cout << "a: " << a << "\tb: " << b << "\tc: " << c << "\td: " << d << endl;
    	 if (a+1 > 3 ){
    		 a = 0;
			apply_surface( 0, 0, dots, screen, &clip[ a ] );		// put the first dot at 0,0
    	 }else{
    		 a = a + 1;
    		 apply_surface( 0, 0, dots, screen, &clip[ a ] );			// put the first dot at 0,0
    	 }
    	 if (b+1 > 3){
    		 b = 0;
 			apply_surface( 540, 0, dots, screen, &clip[ b ] );		// put the second dot at 540, 0
    	 }else{
    		 b = b + 1;
 			apply_surface( 540, 0, dots, screen, &clip[ b ] );		// put the second dot at 540, 0
    	 }
    	 if (c+1 > 3){
    		 c = 0;
				apply_surface( 0, 380, dots, screen, &clip[ c ] );	// put the third dot at 0, 380
    	 }else{
    		 c = c + 1;
				apply_surface( 0, 380, dots, screen, &clip[ c ] );	// put the third dot at 0, 380
    	 }
    	 if (d+1 > 3){
    		 d = 0;
    		 apply_surface( 540, 380, dots, screen, &clip[ d ] );			// put the fourth dot at 540, 380
    	 }else{
    		 d = d + 1;
    		 apply_surface( 540, 380, dots, screen, &clip[ d ] );			// put the fourth dot at 540, 380
    	 }
    	 SDL_Delay(2000);
    //}
		//Update the screen
		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}
		cout << x << endl;
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

    //Free the images and quit SDL
    clean_up();

    return 0;
}
