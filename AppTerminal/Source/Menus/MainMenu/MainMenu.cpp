#include "MainMenu.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

namespace AppTerminal::MenuHandling::Main
{
	void OpenMainMenu()
	{
		bool repeat = false;
		do
		{
			MenuHandling::ClearScreen();

			std::cout << "-----Quiz Game-----\n";
			std::cout << "Press P to play\n";
			std::cout << "Press C to create quiz\n";
			std::cout << "Press E to exit\n";

			if (repeat)
				std::cout << "\nInvalid input, please try again\n";
			std::cout << '\n';

			std::string answer = MenuHandling::GetPlayerInput();

			if (answer.length() == 1)
			{
				switch (answer[0])
				{
				case 'p': //Gameplay
					MenuHandling::GameplayMenu();
					return;

				case 'c': //Creator
					MenuHandling::CreatorMenu();
					return;

				case 'e':
					MenuHandling::ClearScreen(); //Exit
					std::cout << "See you next time!\n";
					return;
				}
			}

			repeat = true;
		} while (repeat);
	}
}