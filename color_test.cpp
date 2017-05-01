#include <stdio.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{


	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("Hello, world!\n");		// regular text
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;30mHello, world!\n"); // - black
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;31mHello, world!\n"); // - red
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	
	printf("\033[22;32mHello\033[22;35m,\033[01;31m world!\n"); // multi color
	sleep(4);
	printf("\33[2J\033[1;1H");
	
	printf("\033[22;32mHello, world!\n"); // - green
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;33mHello, world!\n"); // - brown
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;34mHello, world!\n"); // - blue
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;35mHello, world!\n"); // - magenta
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;36mHello, world!\n"); // - cyan
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[22;37mHello, world!\n"); // - gray
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;30mHello, world!\n"); // - dark gray
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;31mHello, world!\n"); // - light red
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;32mHello, world!\n"); // - light green
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;33mHello, world!\n"); // - yellow
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;34mHello, world!\n"); // - light blue
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;35mHello, world!\n"); // - light magenta
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;36mHello, world!\n"); // - light cyan
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
	printf("\033[01;37mHello, world!\n");	// white/regular text
	sleep(1);
	printf("\033[2J\033[1;1H");		// clear screen
	
}
