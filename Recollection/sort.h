#pragma once
#include <iostream>

// Bubble sort section

/*
Sort the array using bubble sort algorithm.
Params: size - array size, array - array (int) pointer.
*/
void bubble_sort(int size, int* array);

// Shell sort section

/*
Sort the array using shell sort algorithm.
Params: size - array size, array - array (int) pointer.
*/
void shell_sort(int size, int* array);

/*
Find all the required gaps for sorting array using shell algorithm.
Params: size - array size.
Returns array (int) of gaps.
*/
int* get_gaps(int size);

/*
Find gap length for shell sort using Sedgewick formula.
Params: i - number of step in shell sort.
Returns gap length.
*/
int get_gap(int i);

/*
Find the size of array for storing gap sizes for shell algorithm
Params: size - array size.
Returns size of required array.
*/
int get_gaps_size(int size);

// Insertsort

/*
Sort the subarray of the array depending on step.
Params: size - size of array, array - array (int) pointer, from - starting position.
step - gap between elements in subarray (1 sorts all the array).
*/
void insert_sort(int size, int* array, int from, int step);

// Quick sort section

/*
Sort the subarray using quick-sort method.
Params: start - start position, end - end position, array - array (int) pointer.
*/
void quick_sort(int start, int end, int* array);

/*
Find pivot in subarray.
Params: start - start position, end - end position, array - array (int) pointer.
Returns pivot.
*/
int find_pivot(int start, int end, int * array);

// Heap sort section

/*
Sort the array using heap-sort method.
Params: size - array size, array - array (int) pointer.
*/
void heap_sort(int size, int* array);

/*
Builds a heap from given array
Params: size - array size, array - array (int) pointer.
*/
void build_heap(int size, int* array);

// Radix sort section

/*
Get length of longest element (in binary representation).
Params: size - array size, array - array (int) pointer.
Returns length (0 for empty array).
*/
int get_binary_length(int size, int* array);

/*
Get longest element (in binary representation).
Params: size - array size, array - array (int) pointer.
Returns found element (0 if empty array).
*/
int get_longest_element(int size, int *array);

/*
Sort the current array (from lowest to highest) using radix-sort algorithm.
Works only on nonempty arrays.
Params: size - array size, array - array (int) pointer.
*/
void radix_sort(int size, int *array);