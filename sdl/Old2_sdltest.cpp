/* 
 * Compile command:
 * g++ sdltest.cpp -o sdltest -lSDLmain -lSDL -lGL
 */

// specific headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

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

	float myX = 300;
	float myY = 250;
	float width = 50;
	float height = 50;
	float xAxis = 5;
	float yAxis = 5;

	bool left = false, right = false, up = false, down = false;

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
			if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN )
			{
				std::cout << " you hit enter \n";
			}
			// Movement system.
			if ( event.type == SDL_KEYDOWN )
			{
				if ( event.key.keysym.sym == SDLK_LEFT )
				{
					left = true;
				}
				else if ( event.key.keysym.sym == SDLK_RIGHT )
				{
					right = true;
				}
				else if ( event.key.keysym.sym == SDLK_UP )
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
				if ( event.key.keysym.sym == SDLK_LEFT )
				{
					left = false;
				}
				else if ( event.key.keysym.sym == SDLK_RIGHT )
				{
					right = false;
				}
				else if ( event.key.keysym.sym == SDLK_UP )
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
		if ( left == true )
		{
			myX = myX - xAxis;
		}
		if ( right == true )
		{
			myX = myX + xAxis;
		}
		if ( up == true )
		{
			myY = myY - yAxis;
		}
		if ( down == true )
		{
			myY = myY + yAxis;
		}

		// Side and bottom collision
		if ( myX < 0 )
		{
			myX = 0;
		}
		if ( myX+width > 600 )
		{
			myX = 600 - width;
		}
		if ( myY < 0 )
		{
			myY = 0;
		}
		if ( myY+height > 400 )
		{
			myY = 400 - height;
		}
		// Rendering to the screen

		// What we are going to draw, and how we are going to draw it
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); // Start phase

		glOrtho(0, 600, 400, 0, -1, 1); // set the matrix

		glColor4ub(0,0,0,255); 		// black color

		glBegin(GL_QUADS);

		glVertex2f(myX, myY);
		glVertex2f(myX+width, myY);

		glVertex2f(myX+width, myY+height);
		glVertex2f(myX, myY+height);
		
		glEnd();
/*
		glColor4ub(255, 0, 0, 255); // red, green, blue, alpha 4ub gives you alpha

		glBegin(GL_QUADS);	// what we are going to draw 
					// (GL_POINTS, GL_LINES, GL_LINES_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON)
					
		glVertex2f(5, 5);	// top left corner
		glVertex2f(595, 5);	// bottom right conner

		glColor4ub(0, 255, 0, 255);
		glVertex2f(595,395);
		glVertex2f(5, 395);

		glEnd();		// end drawing

		glColor4ub(0,0,0,255); 	// black color

		glBegin(GL_LINES);	// draw a line

		glVertex2f(5,5);
		glVertex2f(595, 395);


		glVertex2f(595,5);
		glVertex2f(5,395);

		glEnd();
*/
		glPopMatrix();		// End phase

		// will actually draw it to the screen
		SDL_GL_SwapBuffers();
		SDL_Delay(1);
	}

	SDL_Quit();
	return 0;
}
