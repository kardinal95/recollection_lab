#pragma once

/*
Stack list
*/
template <typename T>
struct Stack
{
	T* data;
	Stack<T>* next;
};

/*
Add item to the top of the stack.
Params: top - stack top (NULL if empty), data - data to store in stack item.
*/
template <typename T>
void push(Stack<T>* & top, T* data)
{
	// Create new item
	Stack<T>* item = new Stack<T>;
	// Fill the fields
	item->data = data;
	item->next = top;
	// Item is new top
	top = item;
}

/*
Delete the top element of the stack.
Params: top - stack top (NULL if empty).
*/
template <typename T>
void pop(Stack<T>* & top)
{
	// Do nothing if stack is empty
	if (top != NULL)
	{
		// Switch top
		Stack<T>* temp = top;
		top = top->next;
		// Delete previous top
		delete [] temp->data;
		delete temp;
	}
}