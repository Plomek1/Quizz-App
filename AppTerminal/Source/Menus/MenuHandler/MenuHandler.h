#pragma once

#include <string>

void MainMenu();
void CreatorMenu();
void GameplayMenu();

void ClearScreen(char fill = ' ');

std::string GetPlayerInput();
bool GetPlayerIntInput(int& playerInput);
bool ParsePlayerInputToInt(std::string playerInput, int& parsedInput);