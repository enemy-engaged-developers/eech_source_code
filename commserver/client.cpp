#include <iostream>
#include <string>
#include "UDP.h"

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc < 3)
	{
		cout << "Usage: " << argv[0] << " <host> <port> [<command>]" << endl;
		return 1;
	}

	int Port = atoi(argv[2]);
	if (Port <= 0 || Port >= 65534)
		return 1;

	cout << "Connecting to host '" << argv[1] << "', Port " << Port << endl;

	UDPComms comms(argv[1], Port, Port + 1);

	for (;;)
	{
		char buf[1024];

		if (argc > 3)
		{
			strcpy(buf, argv[3]);
			Sleep(1000);
		}
		else
		{
			cin >> buf;
			if (!*buf)
				break;
		}

		int ret = comms.Send(buf);
		memset(buf, 0, sizeof(buf));
		ret = comms.Receive(buf, sizeof(buf));

		cout << "Received [" << buf << "]" << endl;
	}

	return 0;
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
