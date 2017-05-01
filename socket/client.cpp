#include "ClientSocket.h"
#include "SocketException.h"
#include <string>
using namespace std;

int main(int argc, int argv[])
{
	try
	{
		ClientSocket client_socket ("localhost", 3000 );

		string reply;

		try
		{
			client_socket << "Test message.";
			client_socket << reply;
		}
		catch (SocketException&){}
		cout << "We received this response from the server:\n\"" << reply << "\"\n";;
	}
	catch (SocketException& e)
	{
		cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}
