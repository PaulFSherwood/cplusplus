#include <iostream>
#include <stdio.h>
#include <termios.h>  // linux
// #include <conio.h>      // windows
// #include <cstdlib>      // windows
#include "maps.h"
using namespace std;

// using a global so i dont have to use a pointer
char userChar;
int lastX = 0;
int lastY = 0;
int stage = 0;
char myIcon = 'X';
bool iconUp = false, iconDown = false, 
     iconLeft = false, iconRight = false;

// our maps
char arrayField[10][10] = {
					{'|','-','-','-','-','-','-','-','-','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ','-',' ',' ',' ',' ','|'},
					{'|',' ',' ','|',' ','|',' ',' ',' ','|'},
					{'|',' ',' ',' ','-',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|','-','-','-','-','-','-','-','-','|'}
					  };
char stage0[10][10] = {
					{'|','-','-','-','-','-','-','-','-','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ','-',' ',' ',' ',' ','|'},
					{'|',' ',' ','|',' ','|',' ',' ',' ','|'},
					{'|',' ',' ',' ','-',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|','-','-','-','-','-','-','-','-','|'}
					  };
char stage1[10][10] = {
					{'|','-','-','-','-','-','-','-','-','|'},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ','-','-','-',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|','-','-','-','-','-',' ','-','-','|'}
					  };
char stage2[10][10] = {
					{'|','-','-','-','-','-',' ','-','-','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ','|',' ',' ',' ',' ','|'},
					{'|',' ',' ','_','|','_',' ',' ',' ','|'},
					{'|',' ','|',' ',' ',' ','|',' ',' ','|'},
					{'|',' ','-','-','-','-','-',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'|','-','-','-','-','-','-','-','-','|'}
					  };

// function we are going to use 
// this is called function prototyping
// as the real function is below
char getch(void);    // linux
void updateLevel();
void doCollision();
int drawArray(int x, int y);

int main ()
{
	cout << string(50, '\n');      // linux
	// system("CLS");        // windows
	
	// place x in the center to begin with
	drawArray(3, 4);
	bool isRunning = true;
	
	while (isRunning)
	{
		// gets keyboard input and asigns it to userChar
		userChar = getch();
		// clears the screen
		cout << string(50, '\n');      // linux
		// system("CLS");        // windows
		
		// switch statement is used to set the
		// keystate logic
		switch (userChar)
		{
			case 'w':
				iconUp = true;
				break;
			case 'a':
				iconLeft = true;
				break;
			case 's':
				iconDown = true;
				break;
			case 'd':
				iconRight = true;
				break;
			case 'x':
				// use this to close the program
				isRunning = false;
				break;
			default:
				break;
		}
		// update the level
		updateLevel();
		// start our collision detection
		doCollision();
		// we have the new x and y plug it into the 
		// array and print it out.
		drawArray(lastX, lastY);
	}
	return 0;
}
// lets you get keyboard input without the user hitting enter

char getch(void) {                     // this function is a sub for 
        char buf = 0;                  // windows function of the same
        struct termios old = {0};      // name
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

void updateLevel()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if(stage == 0)
			{
				arrayField[x][y] = stage0[x][y];
			}
			if(stage == 1)
			{
				arrayField[x][y] = stage1[x][y];
			}
			if(stage == 2)
			{
				arrayField[x][y] = stage2[x][y];
			}
		}
	}
}
void doCollision()
{
	// little bit of collision before drawing the array.
	if (iconUp)
	{  
		// dont let the myIcon go too far up
		//if (lastX <= 1)
		if (arrayField[lastX-1][lastY] == '|' || arrayField[lastX-1][lastY] ==  '-')
		{
			lastX = lastX;
		}else{
			lastX -= 1;
		}
		if (lastX == 0)
		{
			stage -= 1;
			lastX = 9;
		}
	}
	
	if (iconLeft)
	{
		// dont let myIcon go too far left
		//if (lastY <= 1)
		if (arrayField[lastX][lastY-1] == '|' || arrayField[lastX][lastY-1] == '-')
		{
			lastY = lastY;
		}else{
			lastY -= 1;
		}
		if (lastY == 0)
		{
			stage -= 1;
			lastY = 9;
		}
	}
	
	if (iconDown)
	{
		// dont let myIcon go too far right
		//if (lastX >= 8)
		if (arrayField[lastX+1][lastY] == '|' || arrayField[lastX+1][lastY] == '-')
		{
			lastX = lastX;
		}else{
			lastX += 1;
		}
		if (lastX == 9)
		{
			stage += 1;
			lastX = 0;
		}
	}
	
	if (iconRight)
	{
		// dont let myIcon go too far down
		//if (lastY >= 8)
		if (arrayField[lastX][lastY+1] == '|' || arrayField[lastX][lastY+1] == '-')
		{
			lastY = lastY;
		}else{
			lastY += 1;
		}
		if (lastY == 9)
		{
			stage += 1;
			lastY = 0;
		}
	}
	// change all the keystates back to false
	iconUp = false, iconDown = false, 
	iconLeft = false, iconRight = false;
}

// as the name says it draws the array
int drawArray(int x, int y)
{
	printf("%d,%d||stage:%d\n", lastX, lastY, stage);
	// the icon is set to the x and y coor in the array
	arrayField[x][y] = myIcon;
	
	
	// these two loops print the array.
	int a, b;
	for (a = 0; a <= 9; a++)
	{
		for (b = 0; b <= 9; b++)
		{
			printf("%c", arrayField[a][b]);
		}
		printf("\n");
	}
	
	// set current possition to x and y
	lastX = x;
	lastY = y;
	
	// clear myIcon so we dont get artifacts
	arrayField[x][y] = ' ';
	return 0;
}
