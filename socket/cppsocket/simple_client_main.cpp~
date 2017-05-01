#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"

int main ( int argc, char *argv[] )
{
	try
	{
		ClientSocket client_socket ( "localhost", 30000 );
		
		std::string reply;
		
		while(true)
		{
			try
			{
				std::cout << "please enter your texti\n";
				std::string myString;
				std::cin >> myString;
	  			client_socket << myString;
	  			client_socket >> reply;
			}
			catch ( SocketException& ) {}

      			std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;
		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\n";
	}
	return 0;
}
