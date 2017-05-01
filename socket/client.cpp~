#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
using namespace std;

int main(int argc, int argv[])
{
	cout << "Running....\n";

	try
	{
		// Create the socket
		ServerSocket server (3000 );

		while (true)
		{
			ServerSocket new_sock;
			server.accept (new_sock);

			try
			{
				while(true)
				{
					string data;
					new_sock >> data;
					new_sock << data;
				}
			}
			catch (SocketException&){}
		}
	}
	catch (SocketException& e)
	{
		cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}
