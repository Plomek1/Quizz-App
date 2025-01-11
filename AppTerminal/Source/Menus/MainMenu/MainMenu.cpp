#include "MainMenu.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

void OpenMainMenu()
{
	bool repeat = false;
	while (true)
	{
		ClearScreen();

		std::cout << "-----Quiz Game-----\n";
		std::cout << "Press P to play\n";
		std::cout << "Press C to create quiz\n";
		std::cout << "Press E to exit\n";

		if (repeat) 
			std::cout << "\nPlease enter correct option\n";
		std::cout << '\n';

		char answer = GetPlayerInput();

		switch (answer)
		{
		case 'p': //Gameplay
			GameplayMenu();
			return;

		case 'c': //Creator
			CreatorMenu();
			return;

		case 'e':
			ClearScreen(); //Exit
			std::cout << "See you next time!\n";
			return;
		}

		repeat = true;
	}
}