#include "advinput.h"

/*
Get integer from console input.
Params: storage - input value storage.
Returns false on incorrect input.
*/
bool get_integer(int & storage)
{
	// On default success
	bool success = true;
	int numeric;
	// Char pointer to store char after the found integer
	char *end;
	// Buffer to store input string
	char buf[BUFSIZE];

	// If errors in input or empty input - error
	if (!fgets(buf, BUFSIZE, stdin) || buf[0] == '\n') success = false;
	else
	{
		// Try to convert into num
		numeric = (int)strtol(buf, &end, 10);
		// If something left in buffer except \n - error
		if (*end != '\n') success = false;
		else storage = numeric;
	}
	return success;
}

/*
Get substring.
Returns entered substring
*/
char* get_substring()
{
	char* buffer = new char[BUFSIZE];

	if (!fgets(buffer, BUFSIZE, stdin)) buffer[0] = '\0';
	else buffer[strlen(buffer) - 1] = '\0';

	return buffer;
}