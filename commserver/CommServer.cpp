#include <iostream>

#include "UDP.h"

int Initialise_Shared_Memory(void);
void DeInitialise_Shared_Memory(void);

char *analyseRequest(char *in, size_t len);

int main(int argc, char* argv[])
{
	int debugLevel = 0;
	int Port;

	if (!Initialise_Shared_Memory())
		return 1;

	if ((argc < 2)||(argc > 3))
	{
		std::cout << "EECH CommServer " __DATE__ << std::endl;
		std::cout << "Usage: " << argv[0] << " <Port> [debugLevel]" << std::endl;
		return 1;
	}

	Port = atoi(argv[1]);

	if (Port <= 0 || Port > 65535)
	{
		std::cout << "Please use a Port between 0 and 65536" << std::endl;
		return 1;
	}

	if (argc >= 3)
	{
		debugLevel = atoi(argv[2]);
	}

	{
		UDPComms comms(Port);
		std::cout << "Listening to incoming requests on port " << Port << std::endl;
		std::cout << "Press CTRL-C to quit" << std::endl;

		for (;;)
		{
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));

			int res;
			if ((res = comms.Receive(buffer, sizeof(buffer))) <= 0)
			{
				break;
			}
			buffer[res] = 0;

			if (debugLevel)
			{
				std::cout << "Request received from " << comms.GetClientIP() << std::endl;
				std::cout << "[" << buffer << "]" << std::endl;
			}

			char *response = analyseRequest(buffer, strlen(buffer));
			if (response)
			{
				comms.Send(response);

				if (debugLevel)
				{
					std::cout << "Replied [" << response << "]" << std::endl;
				}

				delete [] response;
			}
		}
	}

	DeInitialise_Shared_Memory();

	return 0;
}
