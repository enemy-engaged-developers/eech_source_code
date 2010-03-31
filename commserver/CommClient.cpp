#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCP.h"

int Initialise_Shared_Memory(void);
void DeInitialise_Shared_Memory(void);

float getValue(int commandID);

const char resp[] = "Arn.Resp:";

float old_values[1024];

int index_to_command(int index)
{
	if (index < 100)
		return index;
	if (index < 150)
		return 450 + index - 100;
	if (index < 250)
		return 500 + index - 150;
	return 0;
}

int main(int argc, char* argv[])
{
	int Port;

	if (!Initialise_Shared_Memory())
		return 1;

	if (argc != 3)
	{
		std::cout << "EECH CommClient " __DATE__ << std::endl;
		std::cout << "Usage: " << argv[0] << " <Host> <Port>" << std::endl;
		return 1;
	}

	Port = atoi(argv[2]);

	if (Port <= 0 || Port > 65535)
	{
		std::cout << "Please use a Port between 0 and 65536" << std::endl;
		return 1;
	}

	std::cout << "EECH CommClient " __DATE__ << std::endl;

	for (int last_index = 0;;)
	{
		try
		{
			{
				time_t now = time(NULL);
				char buf[1024];
				strftime(buf, sizeof(buf), "%x %X Connecting... ", localtime(&now));
				std::cout << buf << std::flush;
			}
			TCPComms comms(argv[1], Port);
			std::cout << "success" << std::endl;

			for (;;)
			{
				char result[65536];
				memcpy(result, resp, sizeof(resp));
				for (int index = 1, command, total = 0; (command = index_to_command(index)) != 0; index++)
				{
					float value = getValue(command);
					if (index > last_index || value != old_values[index])
					{
						sprintf(result + strlen(result), "%i=%.2f:", command, value);
						old_values[index] = value;
						if (++total > 50)
							break;
					}
					if (index > last_index)
						last_index = index;
				}
				if (result[sizeof(resp) - 1])
				{
					strcat(result, "\r\n");
					if (comms.Send(result) <= 0)
						break;
				}

				Sleep(250);
			}
		}
		catch (...)
		{
			std::cout << "failed" << std::endl;
			break;
		}
	}

	DeInitialise_Shared_Memory();

	return 0;
}
