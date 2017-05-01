//============================================================================
// Name        : gotoxy.cpp
// Author      : Stack Overflow
// Version     :
// Copyright   : no copyright
// Description : http://www.daniweb.com/software-development/c/code/216326
//============================================================================

#include <stdio.h>
#include <string.h>

void clrscr(void) {
	int i;

	for (i = 0; i < 100; i++)
		// A bunch of new lines for now. It's blank, hey!
		putchar('\n');
}

int gotoxy(int x, int y) {
	char essq[100];		// String variable to hold the escape sequence
	char xstr[100];		// Strings to hold the x and y coordinates
	char ystr[100];		// Escape sequences must be built with characters

	/*
	** Convert the screen coordinates to strings
	*/
	sprintf(xstr, "%d", x);
	sprintf(ystr, "%d", y);

	/*
	** Build the escape sequence (vertical move)
	*/
	essq[0] = '\0';
	strcat(essq, "\033[");
	strcat(essq, ystr);

	/*
	** Described in man terminfo as vpa=\E[%p1%dd
	** Vertical position absolute
	*/
	strcat(essq, "d");

	/*
	** Horizontal move
	** Horizontal position absolute
	*/
	strcat(essq, "\033[");
	strcat(essq, xstr);
	// Described in man terminfo as hpa=\E[%p1%dG
	strcat(essq, "G");

	/*
	** Execute the escape sequence
	** This will move the cursor to x, y
	*/
	printf("%s", essq);

	return 0;
}

/*
** Example
*/
int main () {
	clrscr();
	gotoxy(2, 0);
	printf("Coordinates: x = 2; y = 0;\n");
	gotoxy(5, 5);
	printf("Coordinates: x = 5; y = 5;\n");

	return 0;
}
