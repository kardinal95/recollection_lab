#include "io.h"
#include <iostream>

#define BUFSIZE 255

bool get_integer(int & storage)
{
	bool success = true;
	int numeric;
	char *end;
	char buf[BUFSIZE];

	if (!fgets(buf, BUFSIZE, stdin) || buf[0] == '\n') success = false;
	else
	{
		numeric = (int)strtol(buf, &end, 10);
		if (*end != '\n') success = false;
		else storage = numeric;
	}
	return success;
}

char* get_substring()
{
	char* buffer = new char[BUFSIZE];

	printf_s("Enter substring to search: ");
	fgets(buffer, BUFSIZE, stdin);
	buffer[strlen(buffer) - 1] = '\0';

	return buffer;
}

void print_status(FILE* text, char* filename, Occurence* core)
{
	if (text == NULL || filename == NULL) printf_s("File is not opened.\n");
	else printf_s("File %s is opened.\n", filename);

	print_amount(core);
}

void change_file(FILE* & text, char* & filename)
{
	if (text != NULL) fclose(text); text = NULL;

	if (filename != NULL) delete[] filename;
	filename = new char[MAX_FILENAME];
	printf_s("Enter new filename: ");
	fgets(filename, MAX_FILENAME, stdin);
	filename[strlen(filename) - 1] = '\0';

	if (fopen_s(&text, filename, "r") != 0)
	{
		text = NULL;
	}
}