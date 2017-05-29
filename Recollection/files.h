#pragma once
#include <iostream>
#include "occurences.h"
#include "advinput.h"

// Maximum file name length
#define MAX_FILENAME 255

/*
Print current file status (not opened / opened at filename).
Also prints how many occurences are in list.
Params: text - file pointer, filename - file name, core - occurence list root node
*/
void search_status(FILE* text, char* filename, Occurence* core);

/*
Change opened file to the file at selected filename.
Params: text - file pointer, filename - filename value variable.
*/
void change_file(FILE* & text, char* & filename);