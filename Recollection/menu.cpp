#include "menu.h"

/*
Draw current menu page.
Params: page - current page.
Returns status.
*/
status draw_menu(menu_page page)
{
	status stat = Success;
	switch (page)
	{
	case Main:
		printf_s("1 - Sort algorithms,\n");
		printf_s("2 - Substring search,\n");
		printf_s("3 - AVL Trees,\n");
		printf_s("4 - Polish notation,\n");
		printf_s("0 - Exit program.\n");
		break;
	case Sort:
		printf_s("1 - Change array size,\n");
		printf_s("2 - Fill with random values,\n");
		printf_s("3 - Fill manually,\n");
		printf_s("4 - Bubble sort,\n");
		printf_s("5 - Shell sort,\n");
		printf_s("6 - Quick sort,\n");
		printf_s("7 - Heap sort,\n");
		printf_s("8 - Radix sort,\n");
		printf_s("0 - Return.\n");
		break;
	case Search:
		printf_s("1 - Change filename,\n");
		printf_s("2 - KMP Search,\n");
		printf_s("3 - BM Search,\n");
		printf_s("4 - RK Search,\n");
		printf_s("5 - Print results,\n");
		printf_s("0 - Return.\n");
		break;
	case AVL:
		printf_s("1 - Add elements (random),\n");
		printf_s("2 - Add elements (manual),\n");
		printf_s("3 - Delete element,\n");
		printf_s("4 - Print tree,\n");
		printf_s("0 - Return.\n");
		break;
	default:
		stat = CriticalError;
		break;
	}
	return stat;
}

/*
Get user selection on menu.
Params: select - selector to store user choice, page - current page.
Returns status.
*/
status get_selection(selector & select, menu_page & page)
{
	status stat = Success;
	// Get user input
	int choice;
	printf_s("Choose option from available: ");
	if (!get_integer(choice)) stat = WrongCommand;
	else
	{
		// Pass for page switches
		select = Pass;
		switch (page)
		{
		case Main:
			switch (choice)
			{
			case 1:	page = Sort; break;
			case 2:	page = Search; break;
			case 3:	page = AVL;	break;
			case 0:	select = Exit; break;
			default: stat = WrongCommand; break;
			}
			break;
		case Sort:
			switch (choice)
			{
			case 1: select = ASize; break;
			case 2: select = AFillRandom; break;
			case 3:	select = AFillManual; break;
			case 4:	select = SortBubble; break;
			case 5: select = SortShell; break;
			case 6: select = SortQuick; break;
			case 7: select = SortHeap; break;
			case 8: select = SortRadix; break;
			case 0: page = Main; break;
			default: stat = WrongCommand; break;
			}
			break;
		case Search:
			switch (choice)
			{
			case 1: select = TChangeFile; break;
			case 2: select = SearchKMP; break;
			case 3: select = SearchBM; break;
			case 4: select = SearchRK; break;
			case 5: select = TPrintResults; break;
			case 0: page = Main; break;
			default: stat = WrongCommand; break;
			}
			break;
		case AVL:
			switch (choice)
			{
			case 1: select = AVLAddRandom; break;
			case 2: select = AVLAddManual; break;
			case 3: select = AVLDelete; break;
			case 4: select = AVLPrint; break;
			case 0: page = Main; break;
			default: stat = WrongCommand; break;
			}
			break;
		default: stat = CriticalError; break;
		}
	}
	return stat;
}

/*
Action handling for arrays and sorts.
Params: select - selected action, size - array size, array - pointer to array.
Returns status.
*/
status make_action(selector select, int & size, int* & array)
{
	status stat = Success;
	switch (select)
	{
	case ASize:
	{
		int result = change_size(size, array);
		if (result == 1) stat = InputValueError;
		else if (result == 2) stat = LessThanZero;
		break;
	}
	case AFillRandom: fill_array(size, array, true); break;
	case AFillManual: fill_array(size, array, false); break;
	case APrint: pretty_print(size, array); break;
	case SortBubble:
	case SortShell:
	case SortQuick:
	case SortHeap:
	case SortRadix:
		// Check existense of array
		if (size != 0 && array != NULL)	switch (select)
		{
			case SortBubble: bubble_sort(size, array); break;
			case SortShell: shell_sort(size, array); break;
			case SortQuick: quick_sort(0, size - 1, array); break;
			case SortHeap: heap_sort(size, array); break;
			case SortRadix: radix_sort(size, array); break;
			default: stat = CriticalError; break;
		}
		else stat = EmptyArray;
		break;
	case Pass: break;
	default: stat = CriticalError;
	}
	return stat;
}

/*
Action handling for text files and substring search.
Params: select - selected action, text - pointer to file, filename - filename pointer (may be NULL),
core - list of occurences pointer.
Returns status.
*/
status make_action(selector select, FILE* & text, char* & filename, Occurence* & core)
{
	status stat = Success;
	switch (select)
	{
	case TPrintStatus: print_status(text, filename, core); break;
	case TChangeFile:
		change_file(text, filename);
		if (text == NULL) stat = FileNotOpened;
		break;
	case SearchKMP:
	case SearchBM:
	case SearchRK:
		if (text == NULL) stat = FileIsNull;
		else
		{
			char* substring = get_substring();
			if (strlen(substring) == 0) stat = EmptySubstring;
			else
			{
				switch (select)
				{
				case SearchKMP: core = search_kmp(text, substring); break;
				case SearchBM: core = search_bm(text, substring); break;
				case SearchRK: core = search_rk(text, substring); break;
				default: stat = CriticalError; break;
				}
			}
		}
		break;
	case TPrintResults: print_all(core, true); break;
	case Pass: break;
	default: stat = CriticalError; break;
	}
	return stat;
}

/*
Action handling for AVL Trees.
Params: select - selected action, root - pointer to tree<int> root.
Returns status.
*/
status make_action(selector select, Tree<int>* & root)
{
	status stat = Success;
	switch (select)
	{
	case AVLAddRandom: add_elements(root, true); break;
	case AVLAddManual: add_elements(root, false); break;
	case AVLDelete:
	case AVLPrint:
		if (root == NULL) stat = EmptyTree;
		else
		{
			switch (select)
			{
			case AVLDelete:
			{
				int* value = new int;
				printf_s("Write value to delete: ");
				if (!get_integer(*value)) stat = InputValueError;
				else root = remove_node(root, value);
				break;
			}
			case AVLPrint: print_tree(root); break;
			}
		}
		break;
	case Pass: break;
	default:
		stat = CriticalError;
		break;
	}
	return stat;
}

void error_handler(status stat)
{
	bool force_exit = false;
	switch (stat)
	{
	case Success:
		break;
	case CriticalError:
		printf_s("Critical error found! Program will be closed!\n");
		force_exit = 1;
		break;
	case WrongCommand: printf_s("Wrong command chosen!\n"); break;
	case EmptyArray: printf_s("Current array is empty!\n"); break;
	case FileNotOpened: printf_s("Cannot open file!\n"); break;
	case FileIsNull: printf_s("File is not opened!\n"); break;
	case EmptySubstring: printf_s("Empty substring search is not supported!\n"); break;
	case EmptyTree: printf_s("Current tree is empty!\n"); break;
	case InputValueError: printf_s("Error in input value!\n"); break;
	case LessThanZero: printf_s("Value cannot be less than zero!\n"); break;
	default:
		printf_s("Critical error found! Program will be closed!\n");
		force_exit = true;
		break;
	}
	system("Pause");
	if (force_exit) exit(1);
}