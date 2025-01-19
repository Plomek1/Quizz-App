#include "MenuHandler.h"

#include "AppRenderer.h"

#include "Menus/MainMenu.h"
#include "Menus/GameplayMenu.h"

#include <iostream>

class MenuHandler;

namespace AppGui
{
    void MenuHandler::StartGame()
    {
        //mainMenu = new MainMenu(*this);
        //gameplayMenu = new GameplayMenu(*this);
        mainMenu = std::make_unique<MainMenu>(*this);
        gameplayMenu = std::make_unique<GameplayMenu>(*this);
        RenderMenu();

        std::cin.get();
    }

    void MenuHandler::ChangeMenu(int nextMenu)
    {
        activeMenu = nextMenu;
        RenderMenu();
    }

    void MenuHandler::RenderMenu()
	{
        switch (activeMenu)
        {
        case 0:
            Render(*mainMenu);
            return;
        case 1:
            Render(*gameplayMenu);
            return;
        }
	}

    MenuHandler::MenuHandler() = default;
    MenuHandler::~MenuHandler() = default;
}