#include "MenuHandler.h"
#include "../MainMenu/MainMenu.h"
#include "../CreatorMenu/CreatorMenu.h"
#include "../GameplayMenu/GameplayMenu.h"

#include <iostream>
#include <windows.h>

void MainMenu() { OpenMainMenu(); }
void CreatorMenu() { OpenCreatorMenu(); }
void GameplayMenu() { OpenGameplayMenu(); }

char GetPlayerInput()
{
    std::string answer;
    std::cin >> answer;
    return char(std::tolower(answer[0]));
}


//https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
void ClearScreen(char fill)
{
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}