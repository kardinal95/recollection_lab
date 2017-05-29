#pragma once
#include <iostream>
#include "occurences.h"
#include "avltree.h"
#include "time.h"

#define MAX_FILENAME 255
#define MAX_SUBSTRING 255

bool get_integer(int & storage);

char* get_substring();

void print_status(FILE* text, char* filename, Occurence* core);

void change_file(FILE* & text, char* & filename);

/*
Print a tree in specific format
*/
template <typename T>
void print_tree(Tree<T>* root)
{
	if (root != NULL)
	{
		// Print the element and its children. Go recursively
		cout << "Element: " << *root->data << endl;
		cout << "Children: ";
		if (root->left == NULL)	cout << "L: none, ";
		else cout << "L: " << *root->left->data << ", ";
		if (root->right == NULL) cout << "R: none.\n";
		else cout << "R: " << *root->right->data << ".\n";

		print_tree(root->left);
		print_tree(root->right);
	}
};

template <typename T>
void add_elements(Tree<T>* & root, bool random)
{
	srand((unsigned)time(NULL));

	int count = 0;
	printf_s("How many elements do you want to add? ");
	if (!get_integer(count) || count < 0)
	{
		printf_s("Incorrect value!\n");
		system("Pause");
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			int* data = new int;
			if (random) *data = (rand());
			else
			{
				printf_s("Enter element number %d value: ", i + 1);
				while (!get_integer(*data)) printf_s("Incorrect. Try again: ");
			}
			Tree<int>* node = make_node(data);
			root = insert_node(root, node);
		}
	}
}