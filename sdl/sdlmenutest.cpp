#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
using namespace std;

void DisplayState(SDL_KeyboardEvent *key)
{
	if (key->type == SDL_KEYUP)
		printf("released: ");
	else
		printf("pressed: ");
}
	
void DisplayModifier(SDL_KeyboardEvent *key)
{
	SDLMod modifier = key->keysym.mod;
	if ( modifier & KMOD_NUM ) printf( " NUM " );
	if ( modifier & KMOD_CAPS ) printf( " CAPS ");
	if ( modifier & KMOD_MODE ) printf( " MODE ");
	if ( modifier & KMOD_LCTRL ) printf( " LCTRL ");
	if ( modifier & KMOD_RCTRL ) printf( " RCTRL ");
	if ( modifier & KMOD_LSHIFT ) printf( " LSHIFT ");
	if ( modifier & KMOD_RSHIFT ) printf( " RSHIFT ");
	if ( modifier & KMOD_LALT ) printf( " LATL ");
	if ( modifier & KMOD_RALT ) printf( " RALT ");
	if ( modifier & KMOD_LMETA ) printf( " KMOD_LMETA ");
	if ( modifier & KMOD_RMETA ) printf( " KMOD_RMETA ");
}

void DisplayKey(SDL_KeyboardEvent *key)
{
	printf("%s\n", SDL_GetKeyName(key->keysym.sym));
}
string choices[3] = 
{	"one",
	"two",
	"three",
};

int main()
{
	// Init the SDL video mode, and creates a small window which can accept 
	// keyboard input when it has focus.
	SDL_Surface *screen;
	
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	atexit(SDL_Quit);
	
	screen = SDL_SetVideoMode(320, 240, 0, SDL_ANYFORMAT);
	if ( screen == NULL ) 
	{
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	for ( int n = 0; n < 3; n++ )
	{	
		cout << "\t" << choices[n] << endl;
	}		
	SDL_Event event;
	int running = 1;
	
	while ( running )
	{
		while( SDL_PollEvent(&event)) 
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
				case SDL_KEYUP:
				DisplayState(&event.key);
				DisplayModifier(&event.key);
				DisplayKey(&event.key);
				break;
				case SDL_QUIT:
				running = 0;
				break;
			}
		}
	}
	return 0;
}
