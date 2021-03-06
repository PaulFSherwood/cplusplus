//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <math.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//The attributes of the circle
const float PI = 3.14159265;
const int CIRCLE_RADIUS = 200;

// The attributes of the square
const int PAD_WIDTH = 20;
const int PAD_HEIGHT = 40;

// the attributes of the ball
const int BALL_WIDTH = 20;
const int BALL_HEIGHT = 20;

// dimensions of the level
//const int LEVEL_WIDTH = 640;
//const int LEVEL_HEIGHT = 480;


//Event handler
SDL_Event event;

//The square
class objects
{
    private:
    //The Pad offsets
    int padX, padY, padN, padRotate, padScaleWidth, padScaleHeight;

    // The Ball offsets
    int ballX, ballY;

    //The velocity of the square
    int padxVel, padyVel;

    // the Ball velocity
    int ballxVel, ballyVel;

    // key control
    bool padLeft, padRight;
    
    // debug ball controll
    bool debugBallUp, debugBallDown, debugBallLeft, debugBallRight;
    // did a collision happen
    bool hasCollision;

    // rotated x,y variables
    float topRightX, topRightY, bottomRightX, bottomRightY, bottomLeftX, bottomLeftY;

    // equation properties
    float slopeLtbM, slopeRtbM, slopeTlrM, slopeBlrM,
	  slopeLtbB, slopeRtbB, slopeTlrB, slopeBlrB,
	  interceptLtbX, interceptRtbX, interceptTlrX, interceptBlrX,
	  interceptLtbY, interceptRtbY, interceptTlrY, interceptBlrY;
	  
    public:
    //Initializes
    objects();

    //Handles key presses
    void handle_input();

    // checks for collision
    void handle_collision();

    //Moves the square
    void move();

    // show some debug output is this how it should be done?
    void debug();

    //Shows the square on the screen
    void show();
};

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

bool init_GL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    // Sets the SDL/OpenGL attributes (memory)
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return false;
    }

    //Initialize OpenGL
    if( init_GL() == false )
    {
        return false;
    }

    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );

    return true;
}

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}

objects::objects()
{
    //Initialize offsets
    padX = 520;
    padY = 240;
    padN = 0;
    padRotate = 0;
    padScaleWidth = 1;
    padScaleHeight = 1;

    // The Ball offsets
    ballX = 320;
    ballY = 240;
	
    // The velocity of the pad
    padxVel = 0;
    padyVel = 0;
    
    // The velocity of the ball
    ballxVel = 3;
    ballyVel = 3;
    
    // key control
    padLeft = false;
    padRight = false;
    
    // debug ball control
    debugBallUp = false;
    debugBallDown = false;
    debugBallLeft = false;
    debugBallRight = false;

    // collision flag
    hasCollision = false;

    // rotated x,y variables
    topRightX = 0;
    topRightY = 0;
    bottomRightX = 0;
    bottomRightY = 0;
    bottomLeftX = 0;
    bottomLeftY = 0;
    
    // equation properties
    // M or slope
    slopeLtbM = 0;
    slopeRtbM = 0;
    slopeTlrM = 0;
    slopeBlrM = 0;
    // B or Y-intercept
    slopeLtbB = 0;
    slopeRtbB = 0;
    slopeTlrB = 0;
    slopeBlrB = 0;
    // intercept of X when Y is zero
    interceptLtbX = 0;
    interceptRtbX = 0;
    interceptTlrX = 0;
    interceptBlrX = 0;
    // intercept of Y when X is zero
    interceptLtbY = 0;
    interceptRtbY = 0;
    interceptTlrY = 0;
    interceptBlrY = 0;
}

void objects::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
	    if (event.key.keysym.sym == SDLK_LEFT)
	    {
		    padLeft = true;
	    }
	    else if (event.key.keysym.sym == SDLK_RIGHT)
	    {
		    padRight = true;
	    }
	    // Ball Movement debug
	    if (event.key.keysym.sym == SDLK_w)
	    {
		    debugBallUp = true;
	    }
	    if (event.key.keysym.sym == SDLK_s)
	    {
		    debugBallDown = true;
	    }
	    if (event.key.keysym.sym == SDLK_a)
	    {
		    debugBallLeft = true;
	    }
	    if (event.key.keysym.sym == SDLK_d)
	    {
		    debugBallRight = true;
	    }
    }
    else if ( event.type == SDL_KEYUP )
    {
	    if (event.key.keysym.sym == SDLK_LEFT)
	    {
		    padLeft = false;
	    }
	    else if (event.key.keysym.sym == SDLK_RIGHT)
	    {
		    padRight = false;
	    }
	    // Ball Movement debug
	    if (event.key.keysym.sym == SDLK_w)
	    {
		    debugBallUp = false;
	    }
	    if (event.key.keysym.sym == SDLK_s)
	    {
		    debugBallDown = false;
	    }
	    if (event.key.keysym.sym == SDLK_a)
	    {
		    debugBallLeft = false;
	    }
	    if (event.key.keysym.sym == SDLK_d)
	    {
		    debugBallRight = false;
	    }
    }
}

void objects::handle_collision()
{
	// values needed for collision 
	topRightX = ((PAD_WIDTH*cos(padN*(PI/180)))-(0*sin(padN*(PI/180))))+padX;
	topRightY = ((PAD_WIDTH*sin(padN*(PI/180)))+(0*cos(padN*(PI/180))))+padY;
	bottomRightX = ((PAD_WIDTH*cos(padN*(PI/180)))-(PAD_HEIGHT*sin(padN*(PI/180))))+padX;
	bottomRightY = ((PAD_WIDTH*sin(padN*(PI/180)))+(PAD_HEIGHT*cos(padN*(PI/180))))+padY;
	bottomLeftX = ((0*cos(padN*(PI/180)))-(PAD_HEIGHT*sin(padN*(PI/180))))+padX;
	bottomLeftY = ((0*sin(padN*(PI/180)))+(PAD_HEIGHT*cos(padN*(PI/180))))+padY;

	
	// finding the left side of pad collision
	// values for LEFT SIDE
	slopeLtbM = ((padY - bottomLeftY) / (padX - bottomLeftX));
	slopeLtbB = padY - (slopeLtbM * padX);
	interceptLtbX = ((0 - slopeLtbB) / slopeLtbM);
	interceptLtbY = ((slopeLtbM * 0) + slopeLtbB);

	// values for RIGHT SIDE
	slopeRtbM = ((topRightY - bottomRightY) / (topRightX - bottomRightX));
	slopeRtbB = topRightY - (slopeRtbM * topRightX);
	interceptRtbX = ((0 - slopeRtbB) / slopeRtbM);
	interceptRtbY = ((slopeRtbM * 0) + slopeRtbB);
	
	// values for TOP SIDE
	slopeTlrM = ((padY - topRightY) / (padX - topRightX));
	slopeTlrB = padY - (slopeTlrM * padX);
	interceptTlrX = ((0 - slopeTlrB) / slopeTlrM);
	interceptTlrY = ((slopeTlrM * 0) + slopeTlrB);
	
	// values for BOTTOM SIDE
	slopeBlrM = ((bottomLeftY - bottomRightY) / (bottomLeftX - bottomRightX));
	slopeBlrB = bottomLeftY - (slopeLtbM * bottomLeftX);
	interceptBlrX = ((0 - slopeBlrB) / slopeBlrM);
	interceptBlrY = ((slopeBlrM * 0) + slopeBlrB);
	
	if (ballX < padX+PAD_WIDTH && ballY < padY+PAD_HEIGHT)
	{
		ballxVel = -ballxVel;
		//std::cout << "collision\n";
	}

	// check collision with the walls
	if (ballX < 0)
	{
		ballxVel = -ballxVel;
	}
	else if (ballX + BALL_WIDTH > 640)
	{
		ballxVel = -ballxVel;
	}
	if (ballY < 0)
	{
		ballyVel = -ballyVel;
	}
	else if (ballY + BALL_HEIGHT > 480)
	{
		ballyVel = -ballyVel;
	}
}
	
void objects::move()
{
	// move the square left or right
	if (padLeft == true)
	{
		padN = padN - 3;
		padX = ((SCREEN_WIDTH/2) + (CIRCLE_RADIUS) *cos(padN*(PI/180)));
		padY = ((SCREEN_HEIGHT/2) + (CIRCLE_RADIUS) *sin(padN*(PI/180)));
           	padRotate = padN;
	}
	if (padRight == true)
	{
		padN = padN + 3;
		padX = ((SCREEN_WIDTH/2) + (CIRCLE_RADIUS) *cos(padN*(PI/180)));
		padY = ((SCREEN_HEIGHT/2) + (CIRCLE_RADIUS) *sin(padN*(PI/180)));
            	padRotate = padN;
	}

	if (padN > 360)
	{
		padN = 0;
	}
	if (padN < 0)
	{
		padN = 360;
	}
	
	// movement for the ball
	//ballX = ballX + ballxVel;
	//ballY = ballY + ballyVel;
	
	// debug ball movement // comment out above;;;
	if (debugBallUp == true)
	{
		ballY = ballY - 1;
	}
	if (debugBallDown == true)
	{
		ballY = ballY + 1;
	}
	if (debugBallLeft == true)
	{
		ballX = ballX - 1;
	}
	if (debugBallRight == true)
	{
		ballX = ballX + 1;
	}
}

void objects::debug()
{
//	int newX, newY;
//	rect info
    std::cout << "======================PAD=====================\n";
    std::cout << "top left: " << padX << ", " << padY << "\ttop right: " << padX+PAD_WIDTH << ", " << padY << "\n";
    std::cout << "botton left: " << padX << ", " << padY+PAD_HEIGHT << "\tbottom right: ";
    std::cout << padX+PAD_WIDTH << ", " << padY+PAD_HEIGHT << "\tTHETA: " << padN << "\n";
    std::cout << "================ALTERED=PAD=2=================\n";
    std::cout << "top left: " << padX << ", " << padY << "\ttop right: " << topRightX << ", " << topRightY << "\n";
    std::cout << "bottom left: " << bottomLeftX << ", " << bottomLeftY << "\t"; 
    std::cout << "bottom right: " << bottomRightX << ", " << bottomRightY << "\n";
    std::cout << "=====================BALL=====================\n";
    std::cout << "top left: " << ballX << ", " << ballY << "\ttop right: " << ballX+BALL_WIDTH << ", " << ballY << "\n";
    std::cout << "bottom left: " << ballX << ", " << ballY+BALL_HEIGHT << "\tbottom right: ";
    std::cout << ballX+BALL_WIDTH << ", " << ballY+BALL_HEIGHT << "\n";
    std::cout << "===========values for padY--topright==========\n";
    std::cout << "slopeLtbM: " << slopeLtbM << "\tslopeRtbM: " << slopeRtbM 
	    << "\tslopeTlrM: " << slopeTlrM << "\tslopeBlrm: " << slopeBlrM << "\n";
    std::cout << "(" << interceptLtbX << ", 0)\t(0, " << interceptLtbY << ")\t(" << interceptRtbX << ", 0)\t(0, " << interceptRtbY << ")\n";
    std::cout << "(" << interceptTlrX << ", 0)\t(0, " << interceptTlrY << ")\t(" << interceptBlrX << ", 0)\t(0, " << interceptBlrY << ")\n";
    /*
    std::cout << "=============test values for new collision=====\n";
    for ( int y = padY+6; y < padY+PAD_HEIGHT; y++)
    {
	    for ( int x = padX+10; x < padX+PAD_WIDTH; x++)
	    {
		    std::cout << ((PAD_WIDTH*cos(padN*(PI/180)))-(0*sin(padN*(PI/180))))+x << ", " << ((PAD_WIDTH*sin(padN*(PI/180)))+(0*cos(padN*(PI/180))))+y << "  ";
	    }
	    std::cout << "\n"; 
    }
    */
}

void objects::show()
{

    //Move to offset
    glTranslatef( padX, padY, 0 );
    glRotatef(padRotate, 0, 0, 1); // rotates along the z axis
    glScalef(padScaleWidth, padScaleHeight, 0);

    // Drawing the PADDLE
    // set color to yellow
    glColor4ub(255, 255, 0, 0);
    //Start quad
    glBegin( GL_QUADS );
    //Draw the paddle
    glVertex3f( 0,         0,          0 );
    glVertex3f( PAD_WIDTH, 0,          0 );
    glVertex3f( PAD_WIDTH, PAD_HEIGHT, 0 );
    glVertex3f( 0,         PAD_HEIGHT, 0 );
    // End quad
    glEnd();
    // update the screen?
    glLoadIdentity();

    // Drawing the BALL
    // set color to red
    glColor4ub(255, 0, 0, 255);
    // Start quad
    glBegin(GL_QUADS);
    // Draw the ball
    glVertex2f(ballX, ballY);
    glVertex2f(ballX+BALL_WIDTH, ballY);
    glVertex2f(ballX+BALL_WIDTH, ballY+BALL_HEIGHT);
    glVertex2f(ballX, ballY+BALL_HEIGHT);
    //End quad
    glEnd();
    // update the screen?
    glLoadIdentity();

    // line 1 color
    glColor4ub(66, 205, 28, 255);
    // enable lines
    glBegin(GL_LINES);
    // draw line 1 **non-inverted**
    glVertex2f(461, 381);
    glVertex2f(481, 381);
    // end line 1
    glEnd();
    // update the screen?
    glLoadIdentity();

    // line 2 color
    glColor4ub(205, 66, 28, 255);
    // enable lines
    glBegin(GL_LINES);
    // draw line 2 **inverted**
    glVertex2f(461, 381);
    glVertex2f(475.14, 395.14);
    // end line 2
    glEnd();
    // update the screen?
    glLoadIdentity();
    
    // try to paint these lines to screen
    glColor4ub(205, 66, 28, 255);
    // enable lines
    glBegin(GL_LINES);
    // draw lines
    glVertex2f(padX, padY);
    glVertex2f(interceptLtbX, 0);
    // end line 2
    glEnd();
    // update the screen?
    glLoadIdentity();

    // paint the Y intercept to scren
    glColor4ub(205, 66, 28, 255);
    // enable lines
    glBegin(GL_LINES);
    // draw lines
    glVertex2f(bottomLeftX, bottomLeftY);
    glVertex2f(0, interceptLtbY);
    // end line 2
    glEnd();
    // Update the screen?
    glLoadIdentity();

    // paint the X intercept to screen for right side
    glColor4ub(205, 66, 28, 255);
    // enable lines
    glBegin(GL_LINES);
    // draw line 2
    glVertex2f(topRightX, topRightY);
    glVertex2f(interceptRtbX, 0);
    // end top right line
    glEnd();
    // Update the screen
    glLoadIdentity();

    // paint the Y intercetp to the screen for the right side bottom
    glColor4ub(205, 66, 28, 255);
    // enable lines
    glBegin(GL_LINES);
    // draw line
    glVertex2f(bottomRightX, bottomRightY);
    glVertex2f(0, interceptRtbY);
    // end bottom right line
    glEnd();
    // Update the screen
    glLoadIdentity();
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char *argv[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Our objects
    objects myObjects;

    //The frame rate regulator
    Timer fps;

    //Wait for user exit
    while( quit == false )
    {
	    //Start the frame timer
	    fps.start();

	    //While there are events to handle
	    while( SDL_PollEvent( &event ) )
	    {
		    //Handle key presses
		    myObjects.handle_input();

		    if( event.type == SDL_QUIT )
		    {
			    quit = true;
		    }
		    if (event.key.keysym.sym == SDLK_TAB)
		    {
		    		myObjects.debug();
			}
	    }
	    // Check for collision
	    myObjects.handle_collision();

	    //Move the square
	    myObjects.move();

	    //Clear the screen
	    glClear( GL_COLOR_BUFFER_BIT );

	    //Show the square
	    myObjects.show();

	    //Update screen
	    SDL_GL_SwapBuffers();

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	}

	//Clean up
	clean_up();

	return 0;
}
