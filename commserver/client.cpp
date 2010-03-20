#include <iostream>
#include <string>
#include "UDP.h"

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc < 3)
	{
		cout << "Usage: " << argv[0] << " <host> <port>" << endl;
		cout << "The program will query the first 30 lamps (ID 501 to 530) of comanche,havoc" << endl << "or hokum" << endl;
		cout << "If EECH is not running all values will be 0" << endl;
		cout << "If you are not flying one of these three helicopters the program will " << endl <<"ASSume you fly the hokum" << endl;
		return 1;
	}

	int Port = atoi(argv[2]);
	if (Port <= 0 || Port >= 65534)
		return 1;

	cout << "Connecting to host '" << argv[1] << "', Port " << Port << endl;

	UDPComms comms(argv[1], Port, Port + 1);

#if 0
	for (int i = 0; i < 30; i++)
	{
		char buf[1024];

		sprintf(buf, "R/%i", 501+i);

		int ret = comms.Send(buf);
		memset(buf, 0, sizeof(buf));
		ret = comms.Receive(buf, sizeof(buf));

		cout << "Received [" << buf << "]" << endl;
	}
#else
	for (;;)
	{
		char buf[1024];

		cin >> buf;
		if (!*buf)
			break;

		int ret = comms.Send(buf);
		memset(buf, 0, sizeof(buf));
		ret = comms.Receive(buf, sizeof(buf));

		cout << "Received [" << buf << "]" << endl;
	}
#endif

	return 0;
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
