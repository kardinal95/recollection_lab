#include "search.h"

#define HASH_BASE 10
#define BUFFER_SIZE 255

// KMP search section

/*
Search for occurences of substring in file (kmp algorithm).
Params: text - file with text, substring - string to search.
Returns list of occurences.
*/
Occurence* search_kmp(FILE* text, char* substring)
{
	// List initialization
	Occurence* core = NULL;
	Occurence* last = NULL;

	// Get shifts for selected substring
	int sublen = strlen(substring);
	int * shifts = get_shifts_kmp(substring);

	// Create buffer for lines in text file
	char * buffer = new char[BUFFER_SIZE];
	// Line counter
	int line = 0;

	// While the end of file is not reached
	while (!feof(text))
	{
		// Get new line
		fgets(buffer, BUFFER_SIZE, text);
		// Increase pointer
		line++;

		int pos = 0, startpos = 0;
		// Until the end of line
		while ((unsigned)startpos + sublen <= strlen(buffer))
		{
			// Nullify the position in substring
			pos = 0;
			// Move forward while the elements are the same and end of substring is not reached
			while (pos < sublen && substring[pos] == buffer[startpos + pos]) pos++;
			// If whole substring passed - found occurence
			if (pos == sublen)
			{
				add_occurence(core, last, line, startpos);
				startpos++;
			}
			// Move forward with required shift
			else
			{
				// Fix for zero element shift
				if (pos == 0) pos++;
				startpos += pos - shifts[pos - 1];
			}
		}
	}

	// Return to the beginning of the file
	rewind(text);
	// Delete buffer (!)
	delete[] buffer;
	return core;
}

/*
Get shift array for substring (kmp algorithm).
Params: substring - string for shifts.
Returns array of shifts.
*/
int* get_shifts_kmp(char* substring)
{
	int subsize = strlen(substring);
	int* shifts = new int[subsize];
	// Find each shift
	for (int i = 1; i <= subsize; i++)
	{
		shifts[i-1] = get_shift_kmp(substring, i);
	}
	return shifts;
}

/*
Get shift for prefix of selected size for substring (kmp algorithm).
Params: substring - string for shifts, size - size of prefix.
Returns shift.
*/
int get_shift_kmp(char* substring, int size)
{
	// Basic shift 0
	int shift = 0;
	// Start with longest prefix (half of the string)
	// Minimum length is 1
	// Stop if shift found
	for (int preflen = size / 2; preflen >= 1 && shift == 0; preflen--)
	{
		int pos = preflen - 1;

		// Compare prefix & suffix symbol by symbol
		// Stop when every symbol is checked or when disrespancy found
		while (pos >= 0 && substring[pos] == substring[size - preflen + pos])
		{
			shift++;
		}
		// If stopped before checking every symbol - nullify (suffix does not fir)
		if (pos >= 0) shift = 0;
	}
	return shift;
}

// BM search section

/*
Search for occurences of substring in file (bm algorithm).
Params: text - file with text, substring - string to search.
Returns list of occurences.
*/
Occurence* search_bm(FILE* text, char* substring)
{
	// List initialization
	Occurence* core = NULL;
	Occurence* last = NULL;

	// Get required tables
	int sublen = strlen(substring);
	int *stops = get_stop_table(substring);
	int *suffs = get_suff_table(substring);

	// Create buffer for lines in text file
	char * buffer = new char[BUFFER_SIZE];
	// Line counter
	int line = 0;

	// While the end of file is not reached
	while (!feof(text))
	{
		// Get new line
		fgets(buffer, BUFFER_SIZE, text);
		// Increase pointer
		line++;

		// Until the end of line
		for (int startpos = sublen - 1; (unsigned)startpos < strlen(buffer);)
		{
			// Length of coinciding suffix
			int sufflen = 0;
			int subpos = sublen - 1;
			int pos = startpos;
			// Shift while symbols are equal
			for (; substring[subpos] == buffer[pos] && subpos >= 0; pos--, subpos--)
			{
				sufflen++;
			}
			// If length of resulting suffix is equal to substring length - occurence found
			if (sufflen == sublen)
			{
				add_occurence(core, last, line, startpos - sublen + 1);
				startpos++;
			}
			else
			{
				// Find the shift of stop symbol
				int stopshift = subpos - stops[buffer[pos] - 32];
				if (stopshift > suffs[sufflen])
				{
					startpos += stopshift;
				}
				else
				{
					startpos += suffs[sufflen];
				}
			}
		}
	}
	
	// Return to the beginning of the file
	rewind(text);
	// Delete buffer (!)
	delete[] buffer;
	return core;
}

/*
Make stop-symbol table for substring (bm algorithm).
Params: substring - string for table.
Returns array of shifts.
*/
int* get_stop_table(char* substring)
{
	// Make array for shifts
	int* stop_table = new int[224];
	int sublen = strlen(substring);

	for (int symcode = 32; symcode < 256; symcode++)
	{
		bool found = false;
		// Basic shift -1
		stop_table[symcode - 32] = -1;
		// Check symbols in substring until found (or end of string)
		for (int pos = sublen - 1; pos >= 0 && !found; pos--)
		{
			if (substring[pos] == (char)symcode)
			{
				// If found - write shift and raise flag
				stop_table[symcode - 32] = pos;
				found = true;
			}
		}
	}
	return stop_table;
}

/*
Make suffix table for substring (bm algorithm).
Params: substring - string for table.
Returns array of shifts.
*/
int* get_suff_table(char* substring)
{
	int sublen = strlen(substring);
	int* suff_table = new int[sublen + 1];

	// Shift for empty suffix
	suff_table[0] = 1;

	// For each suffix
	for (int i = 1; i < sublen + 1; i++)
	{
		bool found = false;
		// While not suffix found
		for (int shift = sublen - 2; shift >= i - 1 && !found; shift--)
		{
			// Check if found suffix
			found = suff_found(substring, shift);
			// Write shift for found suffix
			if (found) suff_table[i] = sublen - 1 - shift;
		}
		// If no suffixes found at all - get shift from previous
		if (!found) suff_table[i] = suff_table[i - 1];
	}
	return suff_table;
}

/*
Check if suffix found (bm algorithm).
Params: substring - string for table, pos - starting position for suffix.
Returns true if suffix found.
*/
bool suff_found(char* substring, int pos)
{
	int sublen = strlen(substring);
	// Default found is true
	bool found = true;
	int suffpos = pos;
	int subpos = sublen - 1;

	// Go through suffix and check symbols
	for (; pos - suffpos < sublen - 1 - pos && !found; suffpos--, subpos--)
	{
		if (substring[suffpos] != substring[subpos])
		{
			found = false;
		}
	}
	// Check previous symbols also
	if (substring[suffpos] != substring[subpos])
	{
		found = false;
	}
	return found;
}

// RK search section

/*
Get hash for substring of given string.
Default parameters for start and end are the first and last positions in given string.
Returns -1 if mistakes in parameters found.
Params: line - string of chars in which the search occurs
optional: start, pos - first and last positions inside given string
Returns hash
*/
int get_hash(char* line, int start = 0, int end = -1)
{
	// Move end to the last position if not set
	if (end == -1)
	{
		end = strlen(line) - 1;
	}
	int result = 0;

	// Avoid errors
	if (end - start < 0 || end < -1 || start >= (int)strlen(line))
	{
		result = -1;
	}
	else
	{
		// Go from start to end positions
		for (int i = start; i <= end; i++)
		{
			// Hash base is powered by the relative position (starting from 0)
			result += (unsigned int)((int)line[i] * pow(HASH_BASE, i - start));
		}
	}
	return result;
}

/*
Check whether the given substring is indeed the occurence by comparing it to the string (from given position).
Compares letter to letter.
Params: line - substring to check, text - string to check in, pos - position in text to start the search
Returns true if occurence is not false-positive
*/
bool is_hash_occurence(char* text, char* line, int pos)
{
	// Assuming it is real occurence
	bool result = true;
	// Position in substring
	int subpos = 0;

	// While not end of string/substring reached and letters are the same
	while (text[pos] == line[subpos] && subpos < (int)strlen(line) && pos < (int)strlen(text))
	{
		// Shift positions forward
		pos++;
		subpos++;
	}

	// If not the whole substring checked - not a real occurence
	if (subpos != strlen(line))
	{
		result = false;
	}

	return result;
}

/*
Search for occurences of substring in file (rk algorithm).
Params: text - file with text, substring - string to search.
Returns list of occurences.
*/
Occurence* search_rk(FILE* text, char* substring)
{
	// Calculate the length to avoid repeated calculations
	int sublen = strlen(substring);
	// Get hash for substring
	int subhash = get_hash(substring);

	// List initialization
	Occurence* core = NULL;
	Occurence* last = NULL;

	// Create buffer for lines in text file
	char * buffer = new char[BUFFER_SIZE];
	// Line counter
	int line = 0;

	// While the end of file is not reached
	while (!feof(text))
	{
		// Get new line
		fgets(buffer, BUFFER_SIZE, text);
		// Increase pointer
		line++;

		// Get first hash for line
		int strhash = get_hash(buffer, 0, sublen - 1);

		// Go through given line
		int pos = 0;
		while (pos + sublen <= (int)strlen(buffer))
		{
			// If hashes coincided - possible occurence found, check for real occurence
			if (subhash == strhash && is_hash_occurence(buffer, substring, pos))
			{
				// If a real occurence - make new element in occurences list
				add_occurence(core, last, line, pos);
			}

			// Recalculate hash for substring of text
			strhash -= get_hash(buffer, pos, pos);
			strhash /= HASH_BASE;
			strhash += (int)(get_hash(buffer, pos + sublen, pos + sublen) * pow(HASH_BASE, sublen - 1));

			// Move forward
			pos++;
		}
	}

	// Return to the beginning of the file
	rewind(text);
	// Delete buffer (!)
	delete[] buffer;
	return core;
}