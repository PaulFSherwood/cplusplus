#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

char string[128];

void txtIt(char *pStr , ...) {
	va_list valist; // Type to hold information about variable arguments
	va_start(valist, pStr); // Initialize a variable argument list
	vsprintf( string , pStr , valist ); // Print formatted variable argument list to string
	va_end(valist); // This macro should be executed before the function
	return;
}

int main(int argc, char *argv[])
{
TTF_Font *font; // Declare a SDL_ttf font : font
TTF_Init(); // Initilize SDL_ttf
font = TTF_OpenFont("./font/arial.ttf",24); // Open a font & set the font size
SDL_Surface *imgTxt; // Store image of the text for blit
SDL_Rect txtRect = {10,150}; // Store (x,y) of text for blit
SDL_Color fColor = {245, 245, 245}; // Font color (R,G,B)

int p1Num = 16;

//txtRect.x = 10;
//txtRect.y = 250;

SDL_Event event;
bool bRun = 1;

SDL_Surface *screen ;

atexit(SDL_Quit);

if( SDL_Init(SDL_INIT_VIDEO) < 0 ) exit(1);

SDL_WM_SetCaption("SDL Window", NULL);

screen = SDL_SetVideoMode( 400 , 300 , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);


while(bRun) {

	//SDL_FillRect(screen , NULL , 0x221122);

	//txtIt("This is a test: %4d", p1Num);//aTick);
	txtIt("%4d", p1Num);
	imgTxt = TTF_RenderText_Solid(font, string, fColor);
	SDL_BlitSurface(imgTxt, NULL, screen, &txtRect);
	SDL_Flip(screen);

	while( SDL_PollEvent( &event ) ){
		switch( event.type ){
			case SDL_KEYDOWN:
				break; // case SDL_KEYDOWN: END
			case SDL_KEYUP:
				if (SDLK_ESCAPE)
				bRun = 0;
				break;
			case SDL_QUIT:
				bRun = 0;
				break;
			default:
				break;
			} // switch( event.type ){ END
		} // while( SDLK_PollEvent( &event ) ){ END
	}; // while(bRun) { END


return 0;
}
