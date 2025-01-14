#pragma once

#include <string>
#include <unordered_map>
#include <functional>

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
	bool HandleSingleCharInput(std::string input, std::unordered_map<char, std::function<void()>>& actions);
}