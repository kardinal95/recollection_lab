#pragma once

/*
Queue list
*/
template <typename T>
struct Queue
{
	T* data;
	Queue<T>* next;
	Queue<T>* prev;
};

/*
Add item to the top of the queue.
Params: top - queue top (NULL if empty), bot - queue bottom (NULL if empty),
data - data to store in queue item.
*/
template <typename T>
void push(Queue<T>* & top, Queue<T>* & bot, T* data)
{
	// Make new queue element
	Queue<T>* item = new Queue<T>;
	item->data = data;
	item->next = top;
	item->prev = NULL;
	// Make necessary changes to previous top
	if (top != NULL) top->prev = item;
	top = item;
	// If queue is empty - the current element is also bottom element
	if (bot == NULL) bot = top;
}

/*
Delete item from the queue (bottom).
Params: top - queue top (NULL if empty), bot - queue bottom (NULL if empty).
*/
template <typename T>
void pop(Queue<T>* & top, Queue<T>* & bot)
{
	// Do nothing if queue is empty
	if (bot != NULL)
	{
		// Switch bottom element
		Queue<T>* temp = bot;
		bot = bot->prev;
		// Make necessary changes to new bottom
		if (bot != NULL) bot->next = NULL;
		// Delete previous bottom
		delete [] temp->data;
		delete temp;
		// If queue is empty - make head NULL
		if (bot == NULL) top = NULL;
	}
}