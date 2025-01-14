#pragma once

#include <string>

namespace AppTerminal::MenuHandling
{
	void MainMenu();
	void CreatorMenu();
	void GameplayMenu();
	void InvalidInputError(bool invalidInput = true);

	void ClearScreen(char fill = ' ');

	std::string GetPlayerInput();
	bool GetPlayerIntInput(int& playerInput);
	bool ParsePlayerInputToInt(std::string playerInput, int& parsedInput);
}