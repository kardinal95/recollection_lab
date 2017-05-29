#include "sort.h"

using namespace std;

// Bubble sort section

/*
Sort the array using bubble sort algorithm.
Params: size - array size, array - array (int) pointer.
*/
void bubble_sort(int size, int* array)
{
	// Swap flag. No swaps indicates already sorted array
	// True to start the cycle
	bool swapped = true;
	// Take each subarray (from biggest to smallest)
	for (int sub = size; sub > 1 && swapped == true; sub--)
	{
		// No swaps at start
		swapped = false;
		// Go from the last to the second position of subarray
		for (int pos = size - 1; pos > size - sub; pos--) {
			if (array[pos - 1] > array[pos])
			{
				// Swap elements if previous is bigger
				swap(array[pos - 1], array[pos]);
				// Raise the flag
				swapped = true;
			}
		}
	}
}

// Shell sort section

/*
Sort the array using shell sort algorithm.
Params: size - array size, array - array (int) pointer.
*/
void shell_sort(int size, int* array)
{
	// First make the array with sizes of gaps
	// Get the size
	int gap_sizes = get_gaps_size(size);
	// Create and fill with gap sizes
	int* seq = get_gaps(gap_sizes);

	// Sort every subarray using insert sort
	for (int current = gap_sizes - 1; current >= 0; current--)
	{
		int gap = seq[current];
		for (int sub = 0; sub < gap; sub++)
		{
			insert_sort(size, array, sub, gap);
		}
	}

}

/*
Find all the required gaps for sorting array using shell algorithm.
Params: size - array size.
Returns array (int) of gaps.
*/
int* get_gaps(int size)
{
	int* seq = new int[size];
	for (int i = 0; i < size; i++)
	{
		seq[i] = get_gap(i);
	}
	return seq;
}

/*
Find gap length for shell sort using Sedgewick formula.
Params: i - number of step in shell sort.
Returns gap length.
*/
int get_gap(int i)
{
	int gap_length;
	// Different formulas for even/noneven numbers
	if (i % 2 == 0)
	{
		gap_length = (int)(9 * pow(2.0, i) - 9 * pow(2.0, i / 2) + 1);
	}
	else
	{
		gap_length = (int)(8 * pow(2.0, i) - 6 * pow(2.0, (i + 1) / 2) + 1);
	}
	return gap_length;
}

/*
Find the size of array for storing gap sizes for shell algorithm
Params: size - array size.
Returns size of required array.
*/
int get_gaps_size(int size)
{
	// Base size
	int gaps_len = 1;
	int step = 0;
	int next = get_gap(step + 1);
	// Stop when exceeds effective size
	while (next * 3 <= size)
	{
		step++;
		gaps_len++;
		next = get_gap(step + 1);
	}
	return gaps_len;
}

// Insert sort section

/*
Sort the subarray of the array depending on step.
Params: size - size of array, array - array (int) pointer, from - starting position.
step - gap between elements in subarray (1 sorts all the array).
*/
void insert_sort(int size, int* array, int from, int step)
{
	int buffer;

	// Do steps until the end of array
	for (int start = from; start < size; start += step)
	{
		// Place current element in buffer
		buffer = array[start];
		// Check all previous elemenets (by used step)
		for (int pos = start - step; pos >= from; pos -= step)
		{
			// Shift the current element to next position if bigger than buffer
			if (array[pos] > buffer)
			{
				array[pos + step] = array[pos];
				// If reached start and haven't placed buffer back - place on the first position
				if (pos == from)
				{
					array[pos] = buffer;
				}
			}
			// If less - position found, place the number from buffer after the current element
			else
			{
				array[pos + step] = buffer;
				// Stop the cycle because buffer is placed
				break;
			}
		}
	}
}

// Quick sort section

/*
Sort the subarray using quick-sort method.
Params: start - start position, end - end position, array - array (int) pointer.
*/
void quick_sort(int start, int end, int* array)
{
	// Array size not less than 2
	if (end - start > 0)
	{
		// Find pivot
		int pivot = find_pivot(start, end, array);
		// Place left on first position, right on last poition
		int left = start, right = end;

		// While they don't cross
		while (left < right)
		{
			// Shift left until number more ore equal to pivot found
			while (array[left] < pivot) left++;
			// Shift right until number less than pivot found
			while (array[right] >= pivot) right--;
			// Swap if needed
			if (left < right) swap(array[left], array[right]);
		}

		// Place left on second pos (subarray size should be cut by 1 at least)
		left = start + 1;
		// Shift until pivot reached
		while (array[left] < pivot) left++;

		// Sort arrays on the left and on the right of pivot
		quick_sort(start, left - 1, array);
		quick_sort(left, end, array);
	}
}

/*
Find pivot in subarray.
Params: start - start position, end - end position, array - array (int) pointer.
Returns pivot.
*/
int find_pivot(int start, int end, int * array)
{
	// Take the first number as minimum and maximum
	int min = array[start], max = array[start];
	// Go through array and change minimum and maximum if needed
	for (int i = start; i <= end; i++) {
		if (array[i] < min) min = array[i];
		if (array[i] > max) max = array[i];
	}
	// Find and return the pivot
	return (min + max) / 2;
}

// Heap sort section

/*
Sort the array using heap-sort method.
Params: size - array size, array - array (int) pointer.
*/
void heap_sort(int size, int* array)
{
	for (int pos = size - 1; pos > 0; pos--)
	{
		// Make heap from given array
		build_heap(pos + 1, array);
		// Swap the last and the first. Exclude last and continue
		swap(array[0], array[pos]);
	}
}

/*
Builds a heap from given array
Params: size - array size, array - array (int) pointer.
*/
void build_heap(int size, int* array)
{
	// Go from bottom to top (exclude lower level)
	for (int head = size / 2 - 1; head >= 0; head--)
	{
		// Swap flag to exclude explicit checks
		bool swapped = true;
		// Take subtree
		int sub = head;
		while (sub * 2 + 1 < size && swapped)
		{
			// Take child
			int child = sub * 2 + 1;
			// If right child exists and bigger - take it instead
			if (child + 1 < size && array[child] < array[child + 1])
			{
				child++;
			}
			// Swap the head with a child if necessary and continue with branch
			if (array[sub] < array[child])
			{
				swap(array[sub], array[child]);
				sub = child;
			}
			else
			{
				// If no swaps - subtree is heap already
				swapped = false;
			}
		}
	}
}

// Radix sort section

/*
Get length of longest element (in binary representation).
Params: size - array size, array - array (int) pointer.
Returns length (0 for empty array).
*/
int get_binary_length(int size, int* array)
{
	int length = 0;
	if (size > 0)
	{
		// Find the longest element first
		// Take absolute value (less checks, no difference)
		int longest = abs(get_longest_element(size, array));
		// Trim bits until the element is equal to 0
		while (longest != 0)
		{
			length++;
			longest = longest >> 1;
		}
	}
	// Return the result
	return length;
}

/*
Get longest element (in binary representation).
Params: size - array size, array - array (int) pointer.
Returns found element (0 if empty array).
*/
int get_longest_element(int size, int *array)
{
	// 0 on empty arrays
	int longest = 0;
	if (size > 0)
	{
		// Assume first is the longest
		longest = array[0];
		// Go through array and check if longer element exist
		for (int i = 1; i < size; i++)
		{
			if (abs(array[i]) > abs(longest)) longest = array[i];
		}
	}
	// Return result
	return longest;
}

/*
Sort the current array (from lowest to highest) using radix-sort algorithm.
Works only on nonempty arrays.
Params: size - array size, array - array (int) pointer.
*/
void radix_sort(int size, int *array)
{
	// Get length of longest element
	int binary_length = get_binary_length(size, array);
	// Arrays for sort process
	int *zero = new int[size];
	int *one = new int[size];
	int zero_size = 0;
	int one_size = 0;
	// For each significant bit (determined by longest element)
	for (int i = 0; i < binary_length; i++)
	{
		zero_size = 0;
		one_size = 0;
		// Split array into two depending on current bit
		for (int k = 0; k < size; k++)
		{
			if ((array[k] >> i) % 2 == 0)
			{
				zero[zero_size] = array[k];
				zero_size++;
			}
			else
			{
				one[one_size] = array[k];
				one_size++;
			}
		}
		// Collect elements back in one array
		// Take zero bits first
		for (int pos = 0; pos < zero_size; pos++) array[pos] = zero[pos];
		for (int pos = 0; pos < one_size; pos++) array[zero_size + pos] = one[pos];
	}
	// Fix negative elements
	zero_size = 0;
	one_size = 0;
	// Positive elements in 'zero' array
	for (int k = 0; k < size; k++)
	{
		if (array[k] > 0)
		{
			zero[zero_size] = array[k];
			zero_size++;
		}
		else
		{
			one[one_size] = array[k];
			one_size++;
		}
	}
	// Finally collect elements back (negative first)
	for (int pos = 0; pos < one_size; pos++) array[pos] = one[pos];
	for (int pos = 0; pos < zero_size; pos++) array[one_size + pos] = zero[pos];
}