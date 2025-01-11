#include "CreatorMenu.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

void OpenCreatorMenu()
{

	bool repeat = false;
	while (true)
	{
		ClearScreen();
		
		std::cout << "-----Creator Menu-----\n";
		std::cout << "Press M to go to main menu\n";

		if (repeat)
			std::cout << "\nPlease enter correct option\n";
		std::cout << '\n';

		char answer = GetPlayerInput();

		switch (answer)
		{
		case 'm': //Main menu
			MainMenu();
			return;
		}

		repeat = true;
	}
}
