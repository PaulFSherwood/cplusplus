/* This tutorial will open a 640 x 480 screen,
** load an image and allow the user to control it
** using the arrow keys. Pressing Space will fire
** a bullet. Collision detection will allow the bullet
** to hit one of the UFO sprites on the screen.
** SDL_TTF is used to increment the player's score
** Pressing escape
** or closing the window will exit the program
*/

#include "main.h"

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern void draw(void);
extern void initPlayer(void);
extern void doPlayer(void);
extern void doEntities(void);
extern void loadAllSprites(void);
extern void loadAllSounds(void);
extern void addUFO(int, int);
extern void doCollisions(void);
extern TTF_Font *loadFont(char *, int);
extern void delay(unsigned int);

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;
	
	/* Start up SDL */
	
	init("Parallel Realities Tutorial 7");
	
	/* Call the cleanup function when the program exits */
	
	atexit(cleanup);
	
	go = 1;
	
	/* Load all the sprites */
	
	loadAllSprites();
	
	/* Load all the sounds */
	
	loadAllSounds();
	
	/* Load the font */
	
	game.font = loadFont("font/blackWolf.ttf", 16);
	
	/* Intialise the player */
	
	initPlayer();
	
	/* A a bunch of UFOs */
	
	addUFO(500, 50);
	addUFO(500, 100);
	addUFO(500, 150);
	addUFO(500, 200);
	addUFO(500, 250);
	addUFO(500, 300);
	
	/* Loop indefinitely for messages */
	
	while (go == 1)
	{
		/* Get the input */
		
		getInput();
		
		/* Update the player's position */
		
		doPlayer();
		
		/* Update the entities */
		
		doEntities();
		
		/* Do the collisions */
		
		doCollisions();
		
		/* Draw everything */
		
		draw();
		
		/* Sleep briefly to stop sucking up all the CPU time */
		
		delay(frameLimit);
		
		frameLimit = SDL_GetTicks() + 16;
	}
	
	/* Exit the program */
	
	exit(0);
}
