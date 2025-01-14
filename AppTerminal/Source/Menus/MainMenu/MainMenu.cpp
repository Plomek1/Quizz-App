#include "MainMenu.h"
#include "../MenuHandler/MenuHandler.h"
#include "../MenuPrompts.h"

#include <iostream>

namespace AppTerminal::MenuHandling::Main
{
	void ExitProgram();

	void OpenMainMenu()
	{
		bool repeat = false;
		do
		{
			MenuHandling::ClearScreen();

			std::cout << MAIN_MENU_PROMPT << '\n';
			std::cout << PLAY_PROMPT << '\n';
			std::cout << CREATE_QUIZ_PROMPT << '\n';
			std::cout << EXIT_PROMPT << '\n';

			MenuHandling::InvalidInputError(repeat);
			std::cout << '\n';

			std::string answer = MenuHandling::GetPlayerInput();
			std::unordered_map<char, std::function<void()>> actions;
			actions[PLAY_OPTION] = []() { GameplayMenu(); }; //Play
			actions[CREATE_QUIZ_OPTION] = []() { CreatorMenu(); };  //Create
			actions[EXIT_OPTION] = []() { ExitProgram(); };	 //Leave

			repeat = !MenuHandling::HandleSingleCharInput(answer, actions);
		} while (repeat);
	}

	void ExitProgram()
	{
		MenuHandling::ClearScreen(); //Exit
		std::cout << GOODBYE_PROMPT << '\n';
	}
}