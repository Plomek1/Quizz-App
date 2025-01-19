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
        menus = std::vector<std::unique_ptr<Menu>>(3);
        menus[0] = std::make_unique<MainMenu>(*this);
        menus[1] = std::make_unique<GameplayMenu>(*this);

        Render(*this);
    }

    void MenuHandler::ChangeMenu(int nextMenu)
    {
        activeMenu = nextMenu;
    }

    void MenuHandler::ExecuteMenuRender()
	{
        menus[activeMenu]->RenderMenu();
	}

    MenuHandler::MenuHandler() = default;
    MenuHandler::~MenuHandler() = default;
}