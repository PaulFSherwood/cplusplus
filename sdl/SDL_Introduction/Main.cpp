//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Introduction Tutorial
// File:    Main.cpp
//////////////////////////////////////////////////////////////////////////////////

// These three lines link in the required SDL components for our project. //
// Alternatively, we could have linked them in our project settings.      //
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_TTF.lib")

#include <stack>	// We'll use the STL stack to store our function pointers
#include "SDL/SDL.h"	// Main SDL header 
#include "SDL/SDL_ttf.h"// True Type Font header
#include "Defines.h"	// Our defines header
#include <string>
#include <iostream>

using namespace std;   

// The STL stack can't take a function pointer as a type //
// so we encapsulate a function pointer within a struct. //
struct StateStruct 
{
	void (*StatePointer)();
};

// Global data //
stack<StateStruct>	g_StateStack;     // Our state stack
SDL_Surface*		g_Bitmap = NULL;  // Our background image
SDL_Surface*		g_Window = NULL;  // Our backbuffer
SDL_Event		g_Event;          // An SDL event structure for input
int			g_Timer;          // Our timer is just an integer

// Functions to handle the three states of the game //
void Menu();
void Game();
void Exit();

// Helper functions for the main game state functions //
void DrawBackground();
void ClearScreen();
void DisplayText(string text, int x, int y, int size, int fR, int fG, int fB, int bR, int bG, int bB);
void HandleMenuInput();
void HandleGameInput();
void HandleExitInput();

// Init and Shutdown functions //
void Init();
void Shutdown();

int main(int argc, char **argv)
{
	Init();
	
	// Our game loop is just a while loop that breaks when our state stack is empty. //
	while (!g_StateStack.empty())
	{
		g_StateStack.top().StatePointer();		
	}

	Shutdown();

	return 0;
}


// This function initializes our game. //
void Init()
{
	// Initiliaze SDL video and our timer. //
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER);
	// Setup our window's dimensions, bits-per-pixel (0 tells SDL to choose for us), //
	// and video format (SDL_ANYFORMAT leaves the decision to SDL). This function    //
	// returns a pointer to our window (back-buffer) which we assign to g_Window.    //
	g_Window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_ANYFORMAT);    
	// Set the title of our window. //
	SDL_WM_SetCaption(WINDOW_CAPTION, 0);
	// Get the number of ticks since SDL was initialized. //
	g_Timer = SDL_GetTicks();

	// Fill our bitmap structure with information. //
	g_Bitmap = SDL_LoadBMP("data/background.bmp");

	// We start by adding a pointer to our exit state, this way //
	// it will be the last thing the player sees of the game.   //
	StateStruct state;
	state.StatePointer = Exit;
	g_StateStack.push(state);

	// Then we add a pointer to our menu state, this will //
	// be the first thing the player sees of our game.    //
	state.StatePointer = Menu;
	g_StateStack.push(state);

	// Initialize the true type font library. //
	TTF_Init();
}

// This function shuts down our game. //
void Shutdown()
{
	// Shutdown the true type font library. //
	TTF_Quit();

	// Free our surfaces. //
	SDL_FreeSurface(g_Bitmap);
	SDL_FreeSurface(g_Window);

	// Tell SDL to shutdown and free any resources it was using. //
	SDL_Quit();
}

// This function handles the game's main menu. From here //
// the player can select to enter the game, or quit.     //
void Menu()
{
	// Here we compare the difference between the current time and the last time we //
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame. //
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleMenuInput();

		// Make sure nothing from the last frame is still drawn. //
		ClearScreen();

		DisplayText("Start (G)ame", 350, 250, 12, 255, 255, 255, 0, 0, 0);
		DisplayText("(Q)uit Game",  350, 270, 12, 255, 255, 255, 0, 0, 0);
			
		// Tell SDL to display our backbuffer. The four 0's will make //
		// SDL display the whole screen. //
		SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		// We've processed a frame so we now need to record the time at which we did it. //
		// This way we can compare this time the next time our function gets called and  //
		// see if enough time has passed between iterations. //
		g_Timer = SDL_GetTicks();
	}	
}

// This function handles the main game. We'll control the   //
// drawing of the game as well as any necessary game logic. //
void Game()
{	
	// Here we compare the difference between the current time and the last time we //
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame. //
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleGameInput();

		// Make sure nothing from the last frame is still drawn. //
		ClearScreen();

		// Draw the background of our little 'game'. //
		DrawBackground();

		// Tell SDL to display our backbuffer. The four 0's will make //
		// SDL display the whole screen. //
		SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		// We've processed a frame so we now need to record the time at which we did it. //
		// This way we can compare this time the next time our function gets called and  //
		// see if enough time has passed between iterations. //
		g_Timer = SDL_GetTicks();
	}	
}

// This function handles the game's exit screen. It will display //
// a message asking if the player really wants to quit.          //
void Exit()
{	
	// Here we compare the difference between the current time and the last time we //
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame. //
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleExitInput();

		// Make sure nothing from the last frame is still drawn. //
		ClearScreen();

		DisplayText("Quit Game (Y or N)?", 350, 250, 12, 255, 255, 255, 0, 0, 0);

		// Tell SDL to display our backbuffer. The four 0's will make //
		// SDL display the whole screen. //
		SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		// We've processed a frame so we now need to record the time at which we did it. //
		// This way we can compare this time the next time our function gets called and  //
		// see if enough time has passed between iterations. //
		g_Timer = SDL_GetTicks();
	}	
}

// This function draws the background //
void DrawBackground() 
{
	// These structures tell SDL_BlitSurface() the location of what //
	// we want to blit and the destination we want it blitted to.   //
	// Presently, we blit the entire surface to the entire screen.  //
	SDL_Rect source      = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };		
	SDL_Rect destination = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	
	// This just 'block-image transfers' our bitmap to our window. //
	SDL_BlitSurface(g_Bitmap, &source, g_Window, &destination);
}

// This function simply clears the back buffer to black. //
void ClearScreen()
{
	// This function just fills a surface with a given color. The //
	// first 0 tells SDL to fill the whole surface. The second 0  //
	// is for black. //
	SDL_FillRect(g_Window, 0, 0);
}

// This function displays text to the screen. It takes the text //
// to be displayed, the location to display it, the size of the //
// text, and the color of the text and background.              //
void DisplayText(string text, int x, int y, int size, int fR, int fG, int fB, int bR, int bG, int bB) 
{
	// Open our font and set its size to the given parameter. //
    TTF_Font* font = TTF_OpenFont("arial.ttf", size);

	SDL_Color foreground  = { fR, fG, fB};   // Text color. //
	SDL_Color background  = { bR, bG, bB };  // Color of what's behind the text. //

	// This renders our text to a temporary surface. There //
	// are other text functions, but this one looks nice.  //
	SDL_Surface* temp = TTF_RenderText_Shaded(font, text.c_str(), foreground, background);

	// A structure storing the destination of our text. //
	SDL_Rect destination = { x, y, 0, 0 };
	
	// Blit the text surface to our window surface. //
	SDL_BlitSurface(temp, NULL, g_Window, &destination);

	// Always free memory! //
	SDL_FreeSurface(temp);

	// Close the font. //
	TTF_CloseFont(font);
}

// This function receives player input and //
// handles it for the game's menu screen.  //
void HandleMenuInput() 
{
	// Fill our event structure with event information. //
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window //
		if (g_Event.type == SDL_QUIT)
		{			
			// While state stack isn't empty, pop //
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}

			return;  // game is over, exit the function
		}

		// Handle keyboard input here //
		if (g_Event.type == SDL_KEYDOWN)
		{
			if (g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
				return;  // this state is done, exit the function 
			}
			// Quit //
			if (g_Event.key.keysym.sym == SDLK_q)
			{
				g_StateStack.pop();
				return;  // game is over, exit the function 
			}
			// Start Game //
			if (g_Event.key.keysym.sym == SDLK_g)
			{
				StateStruct temp;
				temp.StatePointer = Game;
				g_StateStack.push(temp);
				return;  // this state is done, exit the function 
			}
		}
	}
}

// This function receives player input and //
// handles it for the main game state.     //
void HandleGameInput() 
{
	// Fill our event structure with event information. //
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window //
		if (g_Event.type == SDL_QUIT)
		{			
			// While state stack isn't empty, pop //
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}

			return;  // game is over, exit the function
		}

		// Handle keyboard input here //
		if (g_Event.type == SDL_KEYDOWN)
		{
			if (g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
				
				return;  // this state is done, exit the function 
			}			
		}
	}
}

// This function receives player input and //
// handles it for the game's exit screen.  //
void HandleExitInput() 
{
	// Fill our event structure with event information. //
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window //
		if (g_Event.type == SDL_QUIT)
		{			
			// While state stack isn't empty, pop //
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}

			return;  // game is over, exit the function
		}

		// Handle keyboard input here //
		if (g_Event.type == SDL_KEYDOWN)
		{
			if (g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
				
				return;  // this state is done, exit the function 
			}
			// Yes //
			if (g_Event.key.keysym.sym == SDLK_y)
			{
				g_StateStack.pop();
				return;  // game is over, exit the function 
			}
			// No //
			if (g_Event.key.keysym.sym == SDLK_n)
			{
				StateStruct temp;
				temp.StatePointer = Menu;
				g_StateStack.push(temp);
				return;  // this state is done, exit the function 
			}
		}
	}
}

//  Aaron Cox, 2004 //
