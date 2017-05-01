/* compile command:
 * g++ -o sdltest4 sdltest4.cpp -lSDL -lSDLmain -lGL
 */

// Specific headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <string>

// Start of the programs
int main(int argc, char* args[] )
{
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Set OpenGL  memor usage
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

	// Caption of the window
	SDL_WM_SetCaption("our first game", NULL);

	// Size of the window
	SDL_SetVideoMode(600, 400, 32, SDL_OPENGL);

	// Specific the clear color
	glClearColor(1,1,1,1); //RED, GREEN, BLUE, ALPHA

	// What portion of the screen we will display
	glViewport(0, 0, 600, 400);

	// 2D rendering
	glMatrixMode(GL_PROJECTION);

	// Save it
	glLoadIdentity();

	// Disable depth checking
	glDisable(GL_DEPTH_TEST);

	std::cout << "OpenGL is running\n";
	std::cout << "Main loop has started\n";
	
	// handles main loop
	bool isRunning = true;

	// handling events
	SDL_Event event;

	while(isRunning)
	{
		// EVENTS
		while (SDL_PollEvent(&event))
		{
		    if ( event.type == SDL_QUIT ) //If X on windows has been pressed
		    {
			isRunning = false;
		    }

		    if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
		    {
			    isRunning = false;
		    }

		    // if a key has been released and the key is 'r'
		    if (event.type = SDL_KEYUP & event.key.keysym.sym == SDLK_r)
		    {
			glClearColor(1,0,0,1); // red clear color
	    }
	}

      //LOGIC

      //RENDERING
      glClear(GL_COLOR_BUFFER_BIT);


      SDL_GL_SwapBuffers();
    }

  //Quit SDL
  SDL_Quit();

  return 0;
}
