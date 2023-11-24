/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 001

#include "LUtil.h"
float ballX = -0.95;
float ballY =  0.80;
float BALL_WIDTH = 0.15;
float BALL_HEIGHT = 0.15;

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    return true;
}
void update()
{}
void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    //Render quad
    glBegin( GL_QUADS );
        glVertex2f(ballX, ballY);
        glVertex2f(ballX+BALL_WIDTH, ballY);
        glVertex2f(ballX+BALL_WIDTH, ballY+BALL_HEIGHT);
        glVertex2f(ballX, ballY+BALL_HEIGHT);
        // glVertex2f( 200.0, 0.0 );    // bottom left
        // glVertex2f(  0.5f, -0.5f );  // bottom right 
        // glVertex2f(  0.5f,  0.5f );  //    top right 
        // glVertex2f( -0.5f,  0.5f );  //    top left
    glEnd();
    //Update screen
    glutSwapBuffers();
}
