#include "CreatorMenu.h"
#include "../MenuHandler/MenuHandler.h"
#include "../MenuPrompts.h"

#include <iostream>

namespace AppTerminal::MenuHandling::Creator
{
	void OpenCreatorMenu()
	{
		bool repeat = false;
		do
		{
			ClearScreen();

			std::cout << CREATOR_MENU_PROMPT << '\n';
			std::cout << GOTO_MAIN_MENU_PROMPT << '\n';

			InvalidInputError(repeat);
			std::cout << '\n';

			std::string answer = GetPlayerInput();
			std::unordered_map<char, std::function<void()>> actions;
			actions[MAIN_MENU_OPTION] = []() { MainMenu(); }; //Play

			repeat = !HandleSingleCharInput(answer, actions);

		} while (repeat);
	}
}