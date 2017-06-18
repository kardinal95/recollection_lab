#pragma once
#include <iostream>
#include "search.h"
#include "avltree.h"
#include "arrays.h"
#include "sort.h"
#include "advinput.h"
#include "files.h"
#include "polishnotation.h"

// Menu page selector
enum menu_page
{
	Main, Sort, Search, AVL, Polish
};

// Action selector
enum selector
{
	Pass, Exit,
	SortBubble, SortShell, SortQuick, SortHeap, SortRadix,
	ASize, AFillManual, AFillRandom, APrint,
	SearchKMP, SearchBM, SearchRK,
	TChangeFile, TPrintStatus, TPrintResults,
	AVLAddRandom, AVLAddManual, AVLDelete, AVLPrint, AVLDestroy,
	PolishEncodeR, PolishEncode, PolishCalculate, PolishPrint
};

enum status
{
	Success, CriticalError, WrongCommand, EmptyArray, FileNotOpened,
	FileIsNull, EmptySubstring, EmptyTree, InputValueError, LessThanZero,
	IncorrectExpression, NoExpressionStored
};

/*
Draw current menu page.
Params: page - current page.
Returns status.
*/
status draw_menu(menu_page page);

/*
Get user selection on menu.
Params: select - selector to store user choice, page - current page.
Returns status.
*/
status get_selection(selector & select, menu_page & page);

/*
Action handling for arrays and sorts.
Params: select - selected action, size - array size, array - pointer to array.
Returns status.
*/
status make_action(selector select, int & size, int* & array);

/*
Action handling for text files and substring search.
Params: select - selected action, text - pointer to file, filename - filename pointer (may be NULL),
core - list of occurences pointer.
Returns status.
*/
status make_action(selector select, FILE* & text, char* & filename, Occurence* & core);

/*
Action handling for AVL Trees.
Params: select - selected action, root - pointer to tree<int> root.
Returns status.
*/
status make_action(selector select, Tree<int>* & root);

/*
Action handling for Polish notation.
Params: select - selected action, top, bottom - pointers for Queue, reverse - reverse notation flag.
Returns status.
*/
status make_action(selector select, Queue<char>* & top, Queue<char>* & bot, bool & reverse);

/*
Error handling. Exits program with code 1 on critical.
Params: stat - current program status.
*/
void error_handler(status stat);