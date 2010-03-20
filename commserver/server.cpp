#include <iostream>
#include <string>
#include "TCP.h"

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc < 2)
	{
		cout << "Usage: " << argv[0] << " <port>" << endl;
		return 1;
	}

	int Port = atoi(argv[1]);
	if (Port <= 0 || Port >= 65535)
		return 1;

	cout << "Listening to Port " << Port << endl;

	TCPComms comms(Port);

	if (comms.Accept())
	{
		std::cout << "Request accepted from " << comms.GetClientIP() << std::endl;
	}

	for (;;)
	{
		char buf[16384];
		memset(buf, 0, sizeof(buf));
		int res;
		if ((res = comms.Receive(buf, sizeof(buf))) <= 0)
		{
			break;
		}
		buf[res] = 0;
		{
			time_t now = time(NULL);
			char buf[1024];
			strftime(buf, sizeof(buf), "%x %X", localtime(&now));
			std::cout << buf;
		}
		cout << " Received [" << buf << "]" << endl;
	}

	return 0;
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
