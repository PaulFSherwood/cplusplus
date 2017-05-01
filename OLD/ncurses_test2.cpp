#include </usr/include/ncurses.h>

int main()
{
	int ch;

	initscr();				/* Start curses mode			*/
	raw();					/* Line buffering diabled		*/
	keypad(stdscr, TRUE);			/* We get F1, F2 etc...			*/
	noecho();				/* Don't echo() while we do getch	*/

	printw("type any cahacter to see it in bold\n");
	ch = getch();				/* If raw() hadn't been called
						 * we have to press enter before it
						 * gets to the program			*/
	if(ch == KEY_F(1))			/* Without keypad enabled this will	*/
		printw("F1 Key pressed");	/* not get to us either			
						 * characters might have been printed
						 * on screen				*/
	else
	{
		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}
	refresh();				/* Print it on the real screen		*/
	getch();				/* Wait for user input			*/
	endwin();				/* End curses mode			*/

	return 0;
}
