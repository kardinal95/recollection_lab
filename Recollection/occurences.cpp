#include "occurences.h"

#include <iostream>

/*
Add new occurence to list.
Params: core, last - top and bottom elements of list,
line - line in text, position - position in line.
*/
void add_occurence(Occurence* &core, Occurence* &last, int line, int position)
{
	Occurence* p = init_occurence(line, position);

	// Switch core
	if (core == NULL) core = p;
	else
	{
		// Increase amount of elements
		core->amount++;
		last->next = p;
	}
	last = p;
}

/*
Create new occurence.
Params: line - line in text, position - position in line.
Returns pointer to created occurence.
*/
Occurence* init_occurence(int line, int position)
{
	Occurence* p = new Occurence;
	// Basic amount (one element list)
	p->amount = 1;
	p->line = line;
	p->position = position;
	p->next = NULL;

	return p;
}

/*
Print all elements in list.
Params: core - top element of list, shifted - need of pretty shift (first position becomes 1)
*/
void print_all(Occurence* core, bool shifted)
{
	int shift = shifted ? 1 : 0;
	
	if (core == NULL) printf_s("No occurences found.\n");
	else
	{
		while (core != NULL)
		{
			printf_s("Occurence found at line %d, position %d\n", core->line, core->position + shift);
			core = core->next;
		}
	}
}

/*
Print the amount of elements (occurences) in list.
Params: core - top element of list.
*/
void print_amount(Occurence* core)
{
	if (core == NULL || core->amount == 0) printf_s("No occurences in list.\n");
	else printf_s("Occurences in list: %d\n", core->amount);
}