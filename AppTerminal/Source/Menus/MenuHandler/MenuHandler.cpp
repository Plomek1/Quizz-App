#include "MenuHandler.h"
#include "../MainMenu/MainMenu.h"
#include "../CreatorMenu/CreatorMenu.h"
#include "../GameplayMenu/GameplayMenu.h"
#include "../MenuPrompts.h"

#include <iostream>
#include <windows.h>

namespace AppTerminal::MenuHandling
{
    void MainMenu() { Main::OpenMainMenu(); }
    void CreatorMenu() { Creator::OpenCreatorMenu(); }
    void GameplayMenu() { Gameplay::OpenGameplayMenu(); }
    void InvalidInputError(bool invalidInput) { if (invalidInput) std::cout << '\n' << INPUT_INVALID_PROMPT << '\n'; }

    std::string GetPlayerInput()
    {
        std::string answer;
        std::getline(std::cin, answer);
        for (int i = 0; i < answer.length(); i++)
            answer[i] = tolower(answer[i]);

        return answer;
    }

    bool GetPlayerIntInput(int& playerInput)
    {
        try
        {
            std::string answer;
            std::getline(std::cin, answer);
            int input = std::stoi(answer);
            playerInput = input;
            return true;
        }
        catch (const std::invalid_argument& e) { return false; }
    }

    bool ParsePlayerInputToInt(std::string playerInput, int& parsedInput)
    {
        try
        {
            int input = std::stoi(playerInput);
            parsedInput = input;
            return true;
        }
        catch (const std::invalid_argument& e) { return false; }
    }

    bool HandleSingleCharInput(std::string input, std::unordered_map<char, std::function<void()>>& actions)
    {
        if (input.size() != 1) return false;

        char key = input[0];
        if (!actions.contains(key)) return false;
    
        actions[key]();
        return true;
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
}