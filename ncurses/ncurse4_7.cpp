#include <ncurses.h>
#include <iostream>
using namespace std;

void getgrettings();
void clearscr();
void getmenu();
void Sleep(int ms);


int main()
{
	initscr();		/* start ncurses mode */
	raw();			/* turn off signal generation output (i.e. wierd character gettting printed */
	keypad(stdscr, TRUE);	/* enable F1 and other special keys */
	noecho();		/* stop echoing character we use (the arrow keys output wierd stuff) */

	printw("F1 to esc program, press any key to continue\n");
	
	getgrettings();	/* Initial greetings */
	clearscr();		/* Brings curtain dwn/up */
	getmenu();		/* Our menu */
	endwin();		/* end ncurses mode */
	return 0;
}

void getgrettings()
{
	mvprintw(2, 9, "Welcome to the Grant wildlife preserve...");
	refresh();	
	Sleep(500);
	mvprintw(3, 9, "Some things you need to know.");
	refresh();
	Sleep(500);
	mvprintw(4, 9, "We are here to keep our Grant Happy :) ");
	refresh();
	Sleep(500);
	mvprintw(5, 9, "You need to do the following to keep Grant happy ");
	refresh();
	Sleep(5000);
	mvprintw(6, 9, "1. Feed your Grant.");
	refresh();
	Sleep(700);
	mvprintw(7, 9, "2. Teach your Grant. ");
	refresh();
	Sleep(800);
	mvprintw(8, 9, "3. Give your Grant money. ");
	refresh();
	Sleep(900);
	mvprintw(9, 9, "4. Let your grant have fun. ");
	refresh();
	Sleep(1000);
	mvprintw(10, 9, "5. Monitor your Grant's Happieness. ");
	refresh();
	Sleep(3000);
}

void clearscr()
{
////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////DOWN//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|                          ~         ~                     |");
	mvprintw(1,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|~                                               ~~        |");
	mvprintw(1,0, "|                          ~         ~                     |");
	mvprintw(2,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|        ~         ~            ~           ~              |");
	mvprintw(1,0, "|~                                               ~~        |");
	mvprintw(2,0, "|                          ~         ~                     |");
	mvprintw(3,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|                                                          |");
	mvprintw(1,0, "|        ~         ~            ~           ~              |");
	mvprintw(2,0, "|~                                               ~~        |");
	mvprintw(3,0, "|                          ~         ~                     |");
	mvprintw(4,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|   ~                      ~                   ~           |");
	mvprintw(1,0, "|                                                          |");
	mvprintw(2,0, "|        ~         ~            ~           ~              |");
	mvprintw(3,0, "|~                                               ~~        |");
	mvprintw(4,0, "|                          ~         ~                     |");
	mvprintw(5,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|~                                     ~                   |");
	mvprintw(1,0, "|   ~                      ~                   ~           |");
	mvprintw(2,0, "|                                                          |");
	mvprintw(3,0, "|        ~         ~            ~           ~              |");
	mvprintw(4,0, "|~                                               ~~        |");
	mvprintw(5,0, "|                          ~         ~                     |");
	mvprintw(6,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|           ~            ~                         ~       |");
	mvprintw(1,0, "|~                                     ~                   |");
	mvprintw(2,0, "|   ~                      ~                   ~           |");
	mvprintw(3,0, "|                                                          |");
	mvprintw(4,0, "|        ~         ~            ~           ~              |");
	mvprintw(5,0, "|~                                               ~~        |");
	mvprintw(6,0, "|                          ~         ~                     |");
	mvprintw(7,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|                                        ~                 |");
	mvprintw(1,0, "|           ~            ~                         ~       |");
	mvprintw(2,0, "|~                                     ~                   |");
	mvprintw(3,0, "|   ~                      ~                   ~           |");
	mvprintw(4,0, "|                                                          |");
	mvprintw(5,0, "|        ~         ~            ~           ~              |");
	mvprintw(6,0, "|~                                               ~~        |");
	mvprintw(7,0, "|                          ~         ~                     |");
	mvprintw(8,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|~              ~                              ~  ~  ~     |");
	mvprintw(1,0, "|                                        ~                 |");
	mvprintw(2,0, "|           ~            ~                         ~       |");
	mvprintw(3,0, "|~                                     ~                   |");
	mvprintw(4,0, "|   ~                      ~                   ~           |");
	mvprintw(5,0, "|                                                          |");
	mvprintw(6,0, "|        ~         ~            ~           ~              |");
	mvprintw(7,0, "|~                                               ~~        |");
	mvprintw(8,0, "|                          ~         ~                     |");
	mvprintw(9,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|         ~                    ~     ~          ~          |");
	mvprintw(1,0, "|~              ~                              ~  ~  ~     |");
	mvprintw(2,0, "|                                        ~                 |");
	mvprintw(3,0, "|           ~            ~                         ~       |");
	mvprintw(4,0, "|~                                     ~                   |");
	mvprintw(5,0, "|   ~                      ~                   ~           |");
	mvprintw(6,0, "|                                                          |");
	mvprintw(7,0, "|        ~         ~            ~           ~              |");
	mvprintw(8,0, "|~                                               ~~        |");
	mvprintw(9,0, "|                          ~         ~                     |");
	mvprintw(10,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////UP///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|~              ~                              ~  ~  ~     |");
	mvprintw(1,0, "|                                        ~                 |");
	mvprintw(2,0, "|           ~            ~                         ~       |");
	mvprintw(3,0, "|~                                     ~                   |");
	mvprintw(4,0, "|   ~                      ~                   ~           |");
	mvprintw(5,0, "|                                                          |");
	mvprintw(6,0, "|        ~         ~            ~           ~              |");
	mvprintw(7,0, "|~                                               ~~        |");
	mvprintw(8,0, "|                          ~         ~                     |");
	mvprintw(9,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|                                        ~                 |");
	mvprintw(1,0, "|           ~            ~                         ~       |");
	mvprintw(2,0, "|~                                     ~                   |");
	mvprintw(3,0, "|   ~                      ~                   ~           |");
	mvprintw(4,0, "|                                                          |");
	mvprintw(5,0, "|        ~         ~            ~           ~              |");
	mvprintw(6,0, "|~                                               ~~        |");
	mvprintw(7,0, "|                          ~         ~                     |");
	mvprintw(8,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|           ~            ~                         ~       |");
	mvprintw(1,0, "|~                                     ~                   |");
	mvprintw(2,0, "|   ~                      ~                   ~           |");
	mvprintw(3,0, "|                                                          |");
	mvprintw(4,0, "|        ~         ~            ~           ~              |");
	mvprintw(5,0, "|~                                               ~~        |");
	mvprintw(6,0, "|                          ~         ~                     |");
	mvprintw(7,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|~                                     ~                   |");
	mvprintw(1,0, "|   ~                      ~                   ~           |");
	mvprintw(2,0, "|                                                          |");
	mvprintw(3,0, "|        ~         ~            ~           ~              |");
	mvprintw(4,0, "|~                                               ~~        |");
	mvprintw(5,0, "|                          ~         ~                     |");
	mvprintw(6,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|   ~                      ~                   ~           |");
	mvprintw(1,0, "|                                                          |");
	mvprintw(2,0, "|        ~         ~            ~           ~              |");
	mvprintw(3,0, "|~                                               ~~        |");
	mvprintw(4,0, "|                          ~         ~                     |");
	mvprintw(5,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|                                                          |");
	mvprintw(1,0, "|        ~         ~            ~           ~              |");
	mvprintw(2,0, "|~                                               ~~        |");
	mvprintw(3,0, "|                          ~         ~                     |");
	mvprintw(4,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(5,0, "                                                            ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|        ~         ~            ~           ~              |");
	mvprintw(1,0, "|~                                               ~~        |");
	mvprintw(2,0, "|                          ~         ~                     |");
	mvprintw(3,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(4,0, "                                                            ");
	mvprintw(5,0, "                                                            ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|~                                               ~~        |");
	mvprintw(1,0, "|                          ~         ~                     |");
	mvprintw(2,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(3,0, "                                                            ");
	mvprintw(4,0, "                                                            ");
	mvprintw(5,0, "                                                            ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "|                          ~         ~                     |");
	mvprintw(1,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(2,0, "                                                            ");
	mvprintw(3,0, "                                                            ");
	mvprintw(4,0, "                                                            ");
	mvprintw(5,0, "                                                            ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	mvprintw(1,0, "                                                            ");
	mvprintw(2,0, "                                                            ");
	mvprintw(3,0, "                                                            ");
	mvprintw(4,0, "                                                            ");
	mvprintw(5,0, "                                                            ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
////////////////////////////////////////////////////////////////////////////////////////
	mvprintw(0,0, "                                                            ");
	mvprintw(1,0, "                                                            ");
	mvprintw(2,0, "                                                            ");
	mvprintw(3,0, "                                                            ");
	mvprintw(4,0, "                                                            ");
	mvprintw(5,0, "                                                            ");
	mvprintw(6,0, "                                                            ");
	mvprintw(7,0, "                                                            ");
	mvprintw(8,0, "                                                            ");
	mvprintw(9,0, "                                                            ");
	mvprintw(10,0, "                                                            ");
	refresh();
	Sleep(50);
	//sleep(1);
}
void getmenu()
{

	mvprintw(2, 9, "\tone ");
	mvprintw(3, 9, "\ttwo");
	int ch;
	ch = getch();
	
	while((ch = getch()) != KEY_F(1))
	{   switch(ch)
	    {	case KEY_DOWN:
	    	echo();
	    	if ((ch = getch()) == KEY_ENTER){
	    	mvprintw(9,9, "heyheyhey");
	    	}
	    	
	    	else{
	    		mvprintw(2, 9, "\tone");
			attron(A_STANDOUT);
			mvprintw(3, 9, "->\ttwo ");
			attroff(A_STANDOUT);
			}noecho();
			break;
		case KEY_UP:
			attron(A_STANDOUT);
			mvprintw(2, 9, "->\tone ");
			attroff(A_STANDOUT);
			mvprintw(3, 9, "\ttwo");
			break;
		}
	}
	printw("F1 Key Pressed");
}

void Sleep(int ms) {		// http://forums.devshed.com/c-programming-42/linux-version-of-sleep-need-it-in-milliseconds-126723.html
	usleep(ms*1000);	//convert to microseconds
	return;
}

//////////////////////////////////////////
/*		Test Code		*/
//////////////////////////////////////////

/* 
		printw("The pressed key is ");
		attron(A_BOLD)
		attron(A_STANDOUT);
		addstr("I am highlighted!\n");
		attroff(A_STANDOUT);
		mvprintw(2, 9, "%c", ch);
		getmenu();
		clearscr();
		attroff(A_BOLD);
		getch();
	     }printw("F1 Key Pressed");
	     
	*/
