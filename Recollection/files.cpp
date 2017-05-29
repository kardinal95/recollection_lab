#include "files.h"

/*
Print current file status (not opened / opened at filename).
Also prints how many occurences are in list.
Params: text - file pointer, filename - filename, core - occurence list root node
*/
void search_status(FILE* text, char* filename, Occurence* core)
{
	if (text == NULL || filename == NULL) printf_s("File is not opened.\n");
	else printf_s("File %s is opened.\n", filename);

	// Print occurences amount
	print_amount(core);
}

/*
Change opened file to the file at selected filename.
Params: text - file pointer, filename - filename value variable.
*/
void change_file(FILE* & text, char* & filename)
{
	// If file is opened - close it and nullify
	if (text != NULL) fclose(text); text = NULL;
	// Also clear filename
	if (filename != NULL) delete[] filename;

	// Recreate filename
	filename = new char[MAX_FILENAME];
	printf_s("Enter new filename: ");
	filename = get_substring();

	// Try to open file. If failed - nullify file pointer
	if (fopen_s(&text, filename, "r") != 0)
	{
		text = NULL;
	}
}