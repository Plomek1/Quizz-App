#include "CreatorMenu.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

void OpenCreatorMenu()
{

	bool repeat = false;
	do
	{
		ClearScreen();
		
		std::cout << "-----Creator Menu-----\n";
		std::cout << "Press M to go to main menu\n";

		if (repeat)
			std::cout << "\nPlease enter correct option\n";
		std::cout << '\n';

		std::string answer = GetPlayerInput();


		if (answer.length() == 1)
		{
			switch (answer[0])
			{
			case 'm': //Main menu
				MainMenu();
				return;
			}
		}

		repeat = true;
	} while (repeat);
}
