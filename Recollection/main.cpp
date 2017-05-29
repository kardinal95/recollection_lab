#include <iostream>
#include "menu.h"
#include "avltree.h"

using namespace std;

void main()
{
	// Storages
	menu_page page = Main;
	selector select = Pass;
	status stat = Success;

	int size = 0;
	int* array = NULL;

	FILE* text = NULL;
	char* filename = NULL;

	Occurence* core = NULL;

	Tree<int>* root = NULL;

	do
	{
		// Clear old info
		system("CLS");
		// Print status information if needed
		switch (page)
		{
		case Sort:
			make_action(APrint, size, array);
			printf_s("\n");
			break;
		case Search:
			make_action(TPrintStatus, text, filename, core);
			printf_s("\n");
			break;
		// Nothing on other pages
		default: break;
		}
		
		// Draw current menu
		stat = draw_menu(page);
		// Check for critical errors
		if (stat != Success) error_handler(stat);

		// Get user choice
		stat = get_selection(select, page);

		// If everything OK - move forward
		if (stat == Success)
		{
			switch (page)
			{
			case Sort: stat = make_action(select, size, array); break;
			case Search: stat = make_action(select, text, filename, core); break;
			case AVL: stat = make_action(select, root);	break;
			}
		}
		
		// If errors raised - handle them
		if (stat != Success) error_handler(stat);
		// Give user time to see printed results (only if no errors)
		else if (select == TPrintResults || select == AVLPrint) system("Pause");
	} while (select != Exit);

	if (text != NULL) fclose(text);
}