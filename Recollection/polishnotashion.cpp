#include "polishnotation.h"

/*
Check if char is valid for expression.
Params: chr - char to check.
Returns true if valid, false if not.
*/
bool valid_char(char chr)
{
	bool valid = true;
	if ((int)chr < 40 || (int)chr > 57) valid = false;
	if (chr == ',' || chr == '.') valid = false;
	return valid;
}

/*
Get the priority for char in polish notation.
Params: chr - char to get piority.
Returns priority.
*/
int priority(char chr)
{
	int priority = 0;
	if (chr == '+' || chr == '-') priority = 1;
	if (chr == '*' || chr == '/') priority = 2;
	return priority;
}

/*
Encode expression in reverse polish notation. Store result in queue.
Params: top, bot - queue to store result in, input - expression to encode.
Returns false if errors found.
*/
bool encode_reverse(Queue<char>* & top, Queue<char>* & bot, char* input)
{
	// DO NOT use items from queue/stack without copying. Item is deleted from heap when "pop" is called
	// Create stack
	Stack<char>* tmp = NULL;
	// Position in expression string
	int pos = 0;
	// Create buffer and buffer position storage for numbers
	char* buffer = new char[strlen(input)];
	int bufpos = 0;

	// Error flag
	bool incorrect = false;

	// Go through expression. Check for incorrect input meanwhile
	while (valid_char(input[pos]) && (unsigned)pos < strlen(input) && !incorrect)
	{
		// If char is part of number - throw it into buffer
		if (isdigit(input[pos]))
		{
			buffer[bufpos++] = input[pos];
			buffer[bufpos] = '\0';
		}
		else
		{
			// If already have number in buffer - flush it to queue
			if (bufpos != 0)
			{
				push(top, bot, buffer);
				buffer = new char[strlen(input)];
				bufpos = 0;
			}
			switch (input[pos])
			{
			case '(':
			{
				// Add it to stack
				char *sign = new char[2]{ input[pos], '\0' };
				push(tmp, sign);
				break;
			}
			case ')':
			{
				// Move items from stack to queue until '(' found or until end of stack
				while (tmp != NULL && *tmp->data != '(')
				{
					char* sign = new char[2]{ *tmp->data, '\0' };
					push(top, bot, sign);
					pop(tmp);
				}
				// If no '(' found - error
				if (tmp == NULL) incorrect = true;
				// Do not leave it in stack
				else pop(tmp);
				break;
			}
			default:
			{
				// Check priorities and do accordingly
				if (tmp != NULL && priority(input[pos]) <= priority(*tmp->data))
				{
					// Lower priority - move item from stack to queue
					char* sign = new char[2]{ *tmp->data, '\0' };
					push(top, bot, sign);
					pop(tmp);
				}
				// Push current to stack
				char* sign = new char[2]{ input[pos], '\0' };
				push(tmp, sign);
				break;
			}
			}
		}
		// Move next
		pos++;
	}
	// Check for errors
	if ((unsigned)pos < strlen(input)) incorrect = true;
	else if (bufpos != 0 && tmp == NULL) incorrect = true;
	else
	{
		// Move everything left
		if (bufpos != 0) push(top, bot, buffer);
		while (tmp != NULL)
		{
			char* sign = new char[2]{ *tmp -> data, '\0' };
			push(top, bot, sign);
			pop(tmp);
		}
	}
	
	// Clear everything if errors
	if (incorrect)
	{
		top = NULL;
		bot = NULL;
	}
	return !incorrect;
}

/*
Calculate expression in reverse polish notation.
Params: top, bot - queue with encoded expression.
Returns result.
*/
int calculate_reverse(Queue<char>* top, Queue<char>* bot)
{
	// Create stack and current pointer
	Stack<char>* stack = NULL;
	Queue<char>* point = bot;

	// Result
	int result = 0;

	// Go through queue
	while (point != NULL)
	{
		// Check for nums
		if (isdigit(*point->data))
		{
			char* data = new char[strlen(point->data)+1];
			strcpy_s(data, strlen(point->data) + 1, point->data);
			push(stack, data);
		}
		else
		{
			// For storing temp result
			char* tmp = new char[255];
			// Get left and right operands
			int right = strtol(stack->data, NULL, 10);
			pop(stack);
			int left = strtol(stack->data, NULL, 10);
			pop(stack);
			switch (point->data[0])
			{
			case '+': sprintf_s(tmp, 255, "%d", left + right); break;
			case '-': sprintf_s(tmp, 255, "%d", left - right); break;
			case '*': sprintf_s(tmp, 255, "%d", left * right); break;
			case '/': sprintf_s(tmp, 255, "%d", left / right); break;
			default: break;
			}
			// Push result back to tmp
			push(stack, tmp);
		}
		point = point->prev;
	}

	// Convert result to int
	result = strtol(stack->data, NULL, 10);
	return result;
}

/*
Encode expression in reverse polish notation. Store result in queue.
Params: top, bot - queue to store result in, input - expression to encode.
Returns false if errors found.
*/
bool encode(Queue<char>* & top, Queue<char>* & bot, char* input)
{
	// DO NOT use items from queue/stack without copying. Item is deleted from heap when "pop" is called
	// Create stack
	Stack<char>* tmp = NULL;
	// Position in expression string
	int pos = strlen(input)-1;
	// Create buffer and buffer position storage for numbers
	char* buffer = new char[strlen(input)];
	int bufpos = 0;

	// Error flag
	bool incorrect = false;

	// Go through expression. Check for incorrect input meanwhile
	while (valid_char(input[pos]) && (unsigned)pos >= 0 && !incorrect)
	{
		// If char is part of number - throw it into buffer
		if (isdigit(input[pos]))
		{
			buffer[bufpos++] = input[pos];
			buffer[bufpos] = '\0';
		}
		else
		{
			// If already have number in buffer - flush it to queue
			if (bufpos != 0)
			{
				push(top, bot, buffer);
				buffer = new char[strlen(input)];
				bufpos = 0;
			}
			switch (input[pos])
			{
			case ')':
			{
				// Add it to stack
				char *sign = new char[2]{ input[pos], '\0' };
				push(tmp, sign);
				break;
			}
			case '(':
			{
				// Move items from stack to queue until ')' found or until end of stack
				while (tmp != NULL && *tmp->data != ')')
				{
					char* sign = new char[2]{ *tmp->data, '\0' };
					push(top, bot, sign);
					pop(tmp);
				}
				// If no ')' found - error
				if (tmp == NULL) incorrect = true;
				// Do not leave it in stack
				else pop(tmp);
				break;
			}
			default:
			{
				// Check priorities and do accordingly
				if (tmp != NULL && priority(input[pos]) <= priority(*tmp->data))
				{
					// Lower priority - move item from stack to queue
					char* sign = new char[2]{ *tmp->data, '\0' };
					push(top, bot, sign);
					pop(tmp);
				}
				// Push current to stack
				char* sign = new char[2]{ input[pos], '\0' };
				push(tmp, sign);
				break;
			}
			}
		}
		// Move back
		pos--;
	}
	// Check for errors
	if (pos >= 0) incorrect = true;
	else if (bufpos != 0 && tmp == NULL) incorrect = true;
	else
	{
		// Move everything left
		if (bufpos != 0) push(top, bot, buffer);
		while (tmp != NULL)
		{
			char* sign = new char[2]{ *tmp->data, '\0' };
			push(top, bot, sign);
			pop(tmp);
		}
	}

	// Clear everything if errors
	if (incorrect)
	{
		top = NULL;
		bot = NULL;
	}
	return !incorrect;
}

/*
Calculate expression in normal polish notation.
Params: top, bot - queue with encoded expression.
Returns result.
*/
int calculate(Queue<char>* top, Queue<char>* bot)
{
	// Create stack and current pointer
	Stack<char>* stack = NULL;
	Queue<char>* point = top;

	// Result
	int result = 0;

	// Go through queue
	while (point != NULL)
	{
		// Check for nums
		if (isdigit(*point->data))
		{
			if (!isdigit(*stack->data))
			{
				char* data = new char[strlen(point->data) + 1];
				strcpy_s(data, strlen(point->data) + 1, point->data);
				push(stack, data);
			}
			else
			{
				// For storing temp result
				char* tmp = new char[255];
				int right = strtol(point->data, NULL, 10);
				int left = strtol(stack->data, NULL, 10);
				pop(stack);
				switch (stack->data[0])
				{
				case '+': sprintf_s(tmp, 255, "%d", left + right); break;
				case '-': sprintf_s(tmp, 255, "%d", left - right); break;
				case '*': sprintf_s(tmp, 255, "%d", left * right); break;
				case '/': sprintf_s(tmp, 255, "%d", left / right); break;
				default: break;
				}
				pop(stack);
				push(stack, tmp);
			}
		}
		else
		{
			char* sign = new char[2]{ point->data[0], '\0' };
			push(stack, sign);
		}
		point = point->next;
	}

	// Finish calculation
	while (stack != NULL && stack->next != NULL)
	{
		char* tmp = new char[255];
		int right = strtol(stack->data, NULL, 10);
		pop(stack);
		int left = strtol(stack->data, NULL, 10);
		pop(stack);
		switch (stack->data[0])
		{
		case '+': sprintf_s(tmp, 255, "%d", left + right); break;
		case '-': sprintf_s(tmp, 255, "%d", left - right); break;
		case '*': sprintf_s(tmp, 255, "%d", left * right); break;
		case '/': sprintf_s(tmp, 255, "%d", left / right); break;
		default: break;
		}
		pop(stack);
		push(stack, tmp);
	}

	// Convert result to int
	result = strtol(stack->data, NULL, 10);
	return result;
}

/*
Print encoded expression (reversive).
Params: top, bot - queue storing encoded expression.
*/
void print_encoded_reverse(Queue<char>* top, Queue<char>* bot)
{
	Queue<char>* point = bot;
	if (bot == NULL) printf_s("No encoded expression stored.\n");
	else
	{
		printf_s("Encoded expression: ");
		while (point != NULL)
		{
			printf_s("%s", point->data);
			point = point->prev;
		}
		printf_s("\n");
	}
}

/*
Print encoded expression (normal).
Params: top, bot - queue storing encoded expression.
*/
void print_encoded(Queue<char>* top, Queue<char>* bot)
{
	Queue<char>* point = top;
	if (top == NULL) printf_s("No encoded expression stored.\n");
	else
	{
		printf_s("Encoded expression: ");
		while (point != NULL)
		{
			printf_s("%s", point->data);
			point = point->next;
		}
		printf_s("\n");
	}
}