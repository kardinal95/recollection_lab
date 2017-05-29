#pragma once
#include <time.h>
#include <iostream>
#include "io.h"

/*
Change array size. Also destroys the existing array.
Params: size - array size variable, array - pointer to array.
Returns 0 if successful, 1 if wrong input given, 2 if negative size given.
*/
int change_size(int & size, int* & array);

/*
Fills array with values. Random or manual.
Params: size - array size, array - pointer to array, random - random fill flag.
*/
void fill_array(int size, int* & array, bool random);

/*
Pretty print array size and contents.
If array is bigger than 100 elements print first 100.
Params: size - array size, array - pointer to array.
*/
void pretty_print(int size, int* array);