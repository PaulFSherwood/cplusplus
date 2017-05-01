//The headers
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"
#include "mcp3008Spi.h"
#include <sstream>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *message0  = NULL;
SDL_Surface *guage0    = NULL;
SDL_Surface *needle0   = NULL;
SDL_Surface *needle0Rotated   = NULL;
SDL_Surface *message1  = NULL;
SDL_Surface *guage1    = NULL;
SDL_Surface *needle1   = NULL;
SDL_Surface *message2  = NULL;
SDL_Surface *guage2    = NULL;
SDL_Surface *needle2   = NULL;
SDL_Surface *screen    = NULL;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };

// const variables
mcp3008Spi a2d0("/dev/spidev0.0", SPI_MODE_0, 2000000, 8);
mcp3008Spi a2d1("/dev/spidev0.1", SPI_MODE_0, 2000000, 8);
int a2dVal = 0;
int a2dChannel = 0;
unsigned char data[3];

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "TTF Test", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 28 );

//    // loading png's for guages and needles
    guage0 = IMG_Load("gauge.png");
//    guage1 = IMG_Load("gauge.png");
//    guage2 = IMG_Load("gauge.png");
//    if ((!guage0) || (!guage1) || (!guage2))
//    {
//	 std::cout << "guage loading error" << endl;
//    }
    needle0 = IMG_Load("needle.png");
//    needle1 = IMG_Load("needle.png");
//    needle2 = IMG_Load("needle.png");
//    if ((!guage0) || (!guage1) || (!guage2))
//    {
//         std::cout << "needle loading error" << endl;
//    }
    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( message0 );
    SDL_FreeSurface( guage0 );
    SDL_FreeSurface( needle0 );
    SDL_FreeSurface( needle0Rotated );
    SDL_FreeSurface( message1 );
    SDL_FreeSurface( guage1 );
    SDL_FreeSurface( needle1 );
    SDL_FreeSurface( message2 );
    SDL_FreeSurface( guage2 );
    SDL_FreeSurface( needle2 );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void ADC_Grab(int a2dChannel, SDL_Surface*& message, mcp3008Spi& a2d)
{
    data[0] = 1;                                      //  first byte transmitted -> start bit
    data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    data[2] = 0;                                      // third byte transmitted....don't care
    a2d.spiWriteRead(data, sizeof(data) );
    a2dVal = 0;
    a2dVal = (data[1]<< 8) & 0b1100000000;            //merge data[1] & data[2] to get result
    a2dVal |=  (data[2] & 0xff);
    // cout << "ADC: " << a2dVal << endl; 
    //Render the text
    std::stringstream charStrm;
    charStrm << a2dVal;
    message = TTF_RenderText_Solid( font, charStrm.str().c_str(), textColor );
}

void cleanScreen()
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00));
}

int main( int argc, char* args[] )
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
	
	// get message 0
	ADC_Grab(0, message0, a2d0);
	// rotate needle 0
        int angle = ((a2dVal * 180) / 1024) * -1;
        needle0Rotated = rotozoomSurface(needle0, angle, 1, 0);
        SDL_Rect Rect = {100, 190, 0, 0};
	Rect.x -= needle0Rotated->w/2-needle0->w/2;
	Rect.y -= needle0Rotated->h/2-needle0->h/2;
// 	// get message 1
	// ADC_Grab(1, message1, a2d0);
	// // rotate needle 1
        // angle = ((a2dVal * 180) / 1024) * -1;
        // needle1 = rotozoomSurface(needle1, angle, 1, 1);	
	// 
	// // get message 2
	// ADC_Grab(0, message2, a2d1);
	// // rotate needle 2
        // angle = ((a2dVal * 180) / 1024) * -1;
        // needle2 = rotozoomSurface(needle2, angle, 1, 1);	
    
    	//If there was an error in rendering the text
    	// if( (message0 == NULL ) && (message1 == NULL) )
    	// {
    	//     return 1;
    	// }
        // message2 = rotozoomSurface(message2, angle, 1, 1);
        

    	//Apply the images to the screen
    	apply_surface( 100,  10, message0, screen );
	apply_surface( 100, 190,   guage0, screen );
	SDL_BlitSurface(needle0Rotated, NULL, screen, &Rect);
	// apply_surface( 100, 190,  needle0Rotated, screen);

    	// apply_surface(100, 10, message1, screen );
	// apply_surface(100, 90, guage1,   screen );
	// apply_surface(100, 90, needle1,   screen );

    	// apply_surface( 10, 50, message2, screen );
	// apply_surface( 10,130, guage2,   screen );
	// apply_surface( 10,130, needle2,   screen );


    	//Update the screen
    	if( SDL_Flip( screen ) == -1 )
    	{
    	    return 1;
    	}
	cleanScreen();
    }

    //Free surfaces and font then quit SDL_ttf and SDL
    clean_up();

    return 0;
}
