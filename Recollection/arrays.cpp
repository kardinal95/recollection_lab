#include "arrays.h"

/*
Change array size. Also destroys the existing array.
Params: size - array size variable, array - pointer to array.
Returns 0 if successful, 1 if wrong input given, 2 if negative size given.
*/
int change_size(int & size, int* & array)
{
	int newsize = 0, status = 0;
	printf_s("Enter new array size: ");
	// Wrong input
	if (!get_integer(newsize)) status = 1;
	// Negative size
	else if (newsize < 0) status = 2;
	// Everything alright
	else
	{
		size = newsize;
		delete[] array;
		array = NULL;
	}
	return status;
}

/*
Fills array with values. Random or manual.
Params: size - array size, array - pointer to array, random - random fill flag.
*/
void fill_array(int size, int* & array, bool random)
{
	// Nonempty array
	if (size != 0)
	{
		// Delete previous
		delete[] array;
		// Allocate memory for new one
		array = new int[size];
		srand((unsigned)time(NULL));

		for (int i = 0; i < size; i++)
		{
			// Check if random fill required
			if (!random)
			{
				printf_s("Enter element number %d: ", i + 1);
				// Do not allow incorrect input
				while (!get_integer(array[i])) printf_s("Wrong input. Repeat: ");
			}
			else array[i] = rand();
		}
	}
}

/*
Pretty print array size and contents.
If array is bigger than 100 elements print first 100.
Params: size - array size, array - pointer to array.
*/
void pretty_print(int size, int* array)
{
	printf_s("Current array size: %d.\n", size);
	// Do not print contents for empty array
	if (array != NULL)
	{
		// First 100 for big arrays
		if (size > 100) printf_s("Current array contens (first 100 elements):");
		else printf_s("Current array contens (in order):");
		for (int i = 0; i < (size > 100 ? 100 : size) ; i++)
		{
			printf_s(" \'%d\'", array[i]);
		}
		printf_s(".\n");
	}
	else printf_s("Current array is empty.\n");
}