/*
 * Compile command:
 * g++ sdltest.cpp -o sdltest -lSDLmain -lSDL -lGL
 */

// specific headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

struct pad
{
	// The pad variables
public:
	float myX;
	float myY;
	float width;
	float height ;
	float yAxis;			// init yaxis speed.
};

// start of the program
int main()
{
	// initialize SDL
	// audio/video/joystick/everything...
	SDL_Init(SDL_INIT_EVERYTHING);

	// set OpenGL memory usage
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );		// how much memory for opengl to use.
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );		//
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// Caption of the window
	SDL_WM_SetCaption( "Our first game", NULL );

	// Size of the window 32bit colors and sdl_opengl for rendering
	SDL_SetVideoMode( 600, 400, 32, SDL_OPENGL );

	// Specify the clear color
	glClearColor(1,1,1,1);

	// what portion of the screen we will display
	glViewport(0, 0, 600, 400);

	// smooth color transition (fading)
	glShadeModel(GL_SMOOTH);

	// use 2d
	glMatrixMode(GL_PROJECTION);

	// save it
	glLoadIdentity();

	// diable depth checking (no 3d)
	glDisable(GL_DEPTH_TEST);

	std::cout << "SDL is running\n";
	std::cout << "Main loop has started\n";

	// This handles the main loop
	bool isRunning = true;

	// This handles events
	SDL_Event event;

	// ball object
	pad p1;
	p1.myX = 10;
	p1.myY = 330;
	p1.width = 25;
	p1.height = 75;
	p1.yAxis = 5;


	bool up = false, down = false;	// state of the keys

	// main game loop
	while ( isRunning )
	{
		// Events
		while ( SDL_PollEvent(&event) )
		{
			// If the windows was cloased
			if ( event.type == SDL_QUIT )
			{
				isRunning = false;
			}
			// If a button was released and the button was escape
			if  ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
			{
				isRunning = false;
			}
			if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r )
			{
				glClearColor(1,0,0,1);
			}
			// Movement system.
			if ( event.type == SDL_KEYDOWN )
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
			// Logic that should happen for a certain event
		}
		// Logic
		// Padd logic
		if ( up == true )
		{
			p1.myY = p1.myY - p1.yAxis;
		}
		if ( down == true )
		{
			p1.myY = p1.myY + p1.yAxis;
		}
		// top and bottom collision
		if ( p1.myY < 0 )
		{
			p1.myY = 0;
		}
		if ( p1.myY + p1.height > 400 )
		{
			p1.myY = 400 - p1.height;
		}

		// Rendering to the screen
		// What we are going to draw, and how we are going to draw it
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); // Start phase

		glOrtho(0, 600, 400, 0, -1, 1); // set the matrix

		glColor4ub(0,0,0,255); 		// black color

		glBegin(GL_QUADS);

		glVertex2f(p1.myX, p1.myY);
		glVertex2f(p1.myX+p1.width, p1.myY);
		glVertex2f(p1.myX+p1.width, p1.myY+p1.height);
		glVertex2f(p1.myX, p1.myY+p1.height);

		glEnd();

		glBegin(GL_QUADS);
		glEnd();

		glBegin(GL_QUADS);

		glEnd();

		glPopMatrix();		// End phase

		// will actually draw it to the screen
		SDL_GL_SwapBuffers();
		SDL_Delay(1);
	}
	SDL_Quit();
	return 0;
}
