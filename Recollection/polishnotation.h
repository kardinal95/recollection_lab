#pragma once
#include <iostream>
#include "queue.h"
#include "stack.h"

/*
Check if char is valid for expression.
Params: chr - char to check.
Returns true if valid, false if not.
*/
bool valid_char(char chr);

/*
Get the priority for char in polish notation.
Params: chr - char to get piority.
Returns priority.
*/
int priority(char chr);

/*
Encode expression in reverse polish notation. Store result in queue.
Params: top, bot - queue to store result in, input - expression to encode.
Returns false if errors found.
*/
bool encode_reverse(Queue<char>* & top, Queue<char>* & bot, char* input);

/*
Calculate expression in reverse polish notation.
Params: top, bot - queue with encoded expression.
Returns result.
*/
int calculate_reverse(Queue<char>* top, Queue<char>* bot);

/*
Encode expression in normal polish notation. Store result in queue (reversive).
Params: top, bot - queue to store result in, input - expression to encode.
Returns false if errors found.
*/
bool encode(Queue<char>* & top, Queue<char>* & bot, char* input);

/*
Calculate expression in normal polish notation.
Params: top, bot - queue with encoded expression.
Returns result.
*/
int calculate(Queue<char>* top, Queue<char>* bot);

/*
Print encoded expression (reversive).
Params: top, bot - queue storing encoded expression.
*/
void print_encoded_reverse(Queue<char>* top, Queue<char>* bot);

/*
Print encoded expression (normal).
Params: top, bot - queue storing encoded expression.
*/
void print_encoded(Queue<char>* top, Queue<char>* bot);