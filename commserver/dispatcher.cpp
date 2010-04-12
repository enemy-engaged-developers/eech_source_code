#include <vector>
#include <stdio.h>
#include <string.h>

#include "Values.h"

#define QUIET_ALREADY 1

// return either HEAP MEMORY or 0
char* executeCommand(const int commandID)
{
	char *response = new char[1024];
	snprintf(response, 1024, "/%i\\%s", commandID, GetValue(commandID).get_string());
	return response;
}

char *analyseRequest(char *in, const size_t len)
{
	if (in[0] != 'R')
		return 0;

	in[len] = '\0';

	std::vector<char*>requests;
	std::vector<char*>responses;

	static const char sep[] = "/";
	static const char sep2[] = "\\";

	// separate into individual requests
	char *token = strtok( &in[1], sep );
	while( token != NULL )
	{
		requests.push_back(token);		
		/* Get next token: */
		token = strtok( NULL, sep );
	}

	// now separate into command/parameters
	for (size_t i = 0; i < requests.size(); i++)
	{
		int commandID;

		char* token2 = strtok( requests[i], sep2 );
		if (token2 != NULL)
		{
			if (sscanf(token2, "%i", &commandID) != 1)
				continue;
#ifndef QUIET_ALREADY
			printf( "command %s - %i\n", token2, commandID);
#endif
			token2 = strtok( NULL, sep2 );
		}
#if 0
		while( token2 != NULL )
		{
#ifndef QUIET_ALREADY
			/* While there are tokens in "string" */
			printf( "parameter %s\n", token2 );
#endif

			arguments.push_back(token2);

			/* Get next token: */
			token2 = strtok( NULL, sep2 );
		}
#endif

		responses.push_back(executeCommand(commandID));
	}

	char* response = new char[4096];
	strcpy(response, "A");
	for (size_t i = 0; i < responses.size(); i++)
	{
		if (responses[i] == 0)
			continue;

		strcat(response, responses[i]);
		delete [] responses[i];
	}

	return response;
}
