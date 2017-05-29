#pragma once
#include <iostream>
#include "occurences.h"

// KMP search section

/*
Search for occurences of substring in file (kmp algorithm).
Params: text - file with text, substring - string to search.
Returns list of occurences.
*/
Occurence* search_kmp(FILE* text, char* substring);

/*
Get shift array for substring (kmp algorithm).
Params: substring - string for shifts.
Returns array of shifts.
*/
int* get_shifts_kmp(char* substring);

/*
Get shift for prefix of selected size for substring (kmp algorithm).
Params: substring - string for shifts, size - size of prefix.
Returns shift.
*/
int get_shift_kmp(char* substring, int size);

// BM search section

/*
Search for occurences of substring in file (bm algorithm).
Params: text - file with text, substring - string to search.
Returns list of occurences.
*/
Occurence* search_bm(FILE* text, char* substring);

/*
Make stop-symbol table for substring (bm algorithm).
Params: substring - string for table.
Returns array of shifts.
*/
int* get_stop_table(char* substring);

/*
Make suffix table for substring (bm algorithm).
Params: substring - string for table.
Returns array of shifts.
*/
int* get_suff_table(char* substring);

/*
Check if suffix found (bm algorithm).
Params: substring - string for table, pos - starting position for suffix.
Returns true if suffix found.
*/
bool suff_found(char* sublength, int pos);

// RK search section

/*
Get hash for substring of given string.
Default parameters for start and end are the first and last positions in given string.
Returns -1 if mistakes in parameters found.
Params: line - string of chars in which the search occurs
optional: start, pos - first and last positions inside given string
Returns hash
*/
int get_hash(char* substring, int start, int end);

/*
Check whether the given substring is indeed the occurence by comparing it to the string (from given position).
Compares letter to letter.
Params: line - substring to check, text - string to check in, pos - position in text to start the search
Returns true if occurence is not false-positive
*/
bool is_hash_occurence(char* text, char* line, int pos);

/*
Search for occurences of substring in file (rk algorithm).
Params: text - file with text, substring - string to search.
Returns list of occurences.
*/
Occurence* search_rk(FILE* text, char* substring);