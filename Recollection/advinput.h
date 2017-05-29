#pragma once
#include <iostream>

// Maximum char string buffer size
#define BUFSIZE 255

/*
Get integer from console input.
Params: storage - input value storage.
Returns false on incorrect input.
*/
bool get_integer(int & storage);

/*
Get substring.
Returns entered substring
*/
char* get_substring();