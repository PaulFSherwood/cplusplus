/* 
 * Compile command:
 * g++ sdltest.cpp -o sdltest -lSDLmain -lSDL -lGL
 */

// specific headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
  if ( Ay + Ah < By ) return false;
  else if ( Ay > By + Bh ) return false;
  else if ( Ax + Aw < Bx ) return false;
  else if ( Ax > Bx + Bw ) return false;
  return true;
}

struct Brick
{
  float x;
  float y;
  float width;
  float height;
  bool alive;
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

	// The pad variables
	float myX = 300;
	float myY = 370;
	float width = 80;
	float height = 20;
	float xAxis = 5;			// init xaxis speed.

	bool left = false, right = false;	// state of the keys for left and right

	// The ball variables
	float ballX = 50;
	float ballY = 350;
	float ballWH = 30;
	float vellX = 3;
	float vellY = -3;
	
	// Brick elements
	const static int BRICKS = 45;
	Brick bricks[BRICKS];
	for ( int n = 0, x = 4, y = 10; n < BRICKS; n++, x+=66)
	{
	  if ( x > 560)
	  {
	    x = 4;
	    y += 25;
	  }
	  bricks[n].x = x;
	  bricks[n].y = y;
	  bricks[n].width = 60;
	  bricks[n].height = 20;
	  bricks[n].alive = true;
	}
	
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
				if ( event.key.keysym.sym == SDLK_LEFT )
				{
					left = true;
				}
				else if ( event.key.keysym.sym == SDLK_RIGHT )
				{
					right = true;
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
			}
			// Logic that should happen for a certain event
		}
		// Logic
		// Padd logic
		if ( left == true )
		{
			myX = myX - xAxis;
		}
		if ( right == true )
		{
			myX = myX + xAxis;
		}
		// Side collision
		if ( myX < 0 )
		{
			myX = 0;
		}
		if ( myX+width > 600 )
		{
			myX = 600 - width;
		}
		
		// X ball logic and collision check.
		ballX = ballX + vellX;
		
		for ( int n = 0; n < BRICKS; n++)
		{
		  if ( bricks[n].alive == true )
		  {
		      if ( checkCollision(ballX, ballY, ballWH, ballWH, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height ))
		      {
			vellX = -vellX;
			bricks[n].alive = false;
			break;
		      }
		  }
		}
		// Y ball logic and collision check.
		ballY = ballY + vellY;
		for ( int n = 0; n < BRICKS; n++)
		{
		  if ( bricks[n].alive == true )
		  {
		      if ( checkCollision(ballX, ballY, ballWH, ballWH, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height ))
		      {
			vellY = -vellY;
			bricks[n].alive = false;
			break;
		      }
		  }
		}
		
		if ( ballX < 0 )
		{
		  vellX = -vellX;
		}
		else if ( ballX + ballWH > 600 )
		{
		  vellX = -vellX;
		}
		
		if ( ballY < 0 )
		{
		  vellY = -vellY;
		}
		else if ( ballY + ballWH > 400 )
		{
			// The pad variables
			myX = 300;
			myY = 370;
			width = 80;
			height = 20;
			xAxis = 5;			// init xaxis speed.

			//left = false, right = false;	// state of the keys for left and right

			// The ball variables
			ballX = 50;
			ballY = 350;
			ballWH = 30;
			vellX = 3;
			vellY = -3;
			
			for ( int n = 0; n < BRICKS; n++)
			{
			      bricks[n].alive = true;
			      
			      SDL_Delay(80);
			}
		}
		
		if ( checkCollision(ballX, ballY, ballWH, ballWH, myX, myY, width, height) == true )
		{
		  vellY = -vellY;
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
		
		// the ball
		glColor4ub(255,0,0,255);
		
		glBegin(GL_QUADS);
		glVertex2f(ballX, ballY);
		glVertex2f(ballX+ballWH, ballY);
		glVertex2f(ballX+ballWH, ballY+ballWH);
		glVertex2f(ballX, ballY+ballWH);
		glEnd();
		
		glColor4ub(0,0,255,255); // blue color
		
		glBegin(GL_QUADS);
		
		for ( int n = 0; n < BRICKS; n++ )
		{
		  if ( bricks[n].alive == true )
		  {
		      if ( n%2 == 0 ) glColor4ub(122,0,255,255);
		      else glColor4ub(0,0,255,255);
		      glVertex2f(bricks[n].x,bricks[n].y);
		      glVertex2f(bricks[n].x+bricks[n].width,bricks[n].y);
		      glVertex2f(bricks[n].x+bricks[n].width,bricks[n].y+bricks[n].height);
		      glVertex2f(bricks[n].x,bricks[n].y+bricks[n].height);
		  }
		}
		glEnd();
		
		glPopMatrix();		// End phase

		// will actually draw it to the screen
		SDL_GL_SwapBuffers();
		SDL_Delay(1);
	}
	SDL_Quit();
	return 0;
}
