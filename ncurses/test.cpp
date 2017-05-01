#include <ncurses.h>

int main()
{
	initscr();		/* Start curses mode		*/
	printw("Hey");		/* Print hey			*/
	refresh();		/* Print it to the real screen	*/
	getch();		/* Wait for user input		*/
	endwin();		/* End curses mode		*/
	
	return 0;
}
