//The headers
#include "SDL.h"
#include "SDL_ttf.h"
#include "mcp3008Spi.h"
#include <sstream>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *message0 = NULL;
SDL_Surface *message1 = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };

// const variables
mcp3008Spi a2d0("/dev/spidev0.0", SPI_MODE_0, 2000000, 8);
mcp3008Spi a2d0("/dev/spidev0.1", SPI_MODE_0, 2000000, 8);
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
    SDL_FreeSurface( message1 );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void ADC_Grab(int a2dChannel, SDL_Surface*& message)
{
    data[0] = 1;                                      //  first byte transmitted -> start bit
    data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    data[2] = 0;                                      // third byte transmitted....don't care
    a2d0.spiWriteRead(data, sizeof(data) );
    a2dVal = 0;
    a2dVal = (data[1]<< 8) & 0b1100000000;            //merge data[1] & data[2] to get result
    a2dVal |=  (data[2] & 0xff);
    cout << "ADC: " << a2dVal << endl; 
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
	ADC_Grab(0, message0);
	ADC_Grab(1, message1);
    
    	//If there was an error in rendering the text
    	if( (message0 == NULL ) && (message1 == NULL) )
    	{
    	    return 1;
    	}
    	
    	//Apply the images to the screen
    	apply_surface(  0, 150, message0, screen );
    	apply_surface(100, 150, message1, screen );

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
