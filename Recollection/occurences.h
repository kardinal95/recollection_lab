#pragma once

struct Occurence
{
	// Position in line (first in line - 0)
	int position;
	// Line in text
	int line;
	// Amount of occurences total (only important on core)
	int amount;

	Occurence* next;
};

/*
Add new occurence to list.
Params: core, last - top and bottom elements of list,
line - line in text, position - position in line.
*/
void add_occurence(Occurence* &core, Occurence* &last, int line, int position);

/*
Create new occurence.
Params: line - line in text, position - position in line.
Returns pointer to created occurence.
*/
Occurence* init_occurence(int line, int position);

/*
Print all elements in list.
Params: core - top element of list, shifted - need of pretty shift (first position becomes 1)
*/
void print_all(Occurence* core, bool shifted);

/*
Print the amount of elements (occurences) in list.
Params: core - top element of list.
*/
void print_amount(Occurence* core);