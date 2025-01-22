#include "MenuHandler.h"

#include "AppRenderer.h"
#include "Menus/MainMenu.h"
#include "Menus/GameplayMenu.h"
#include "Menus/CreatorMenu.h"

namespace AppGui
{
    void MenuHandler::StartGame()
    {
        appRenderer = std::make_unique<AppRenderer>();

        menus = std::vector<std::unique_ptr<Menu>>(3);
        menus[0] = std::make_unique<MainMenu>(*this);
        menus[1] = std::make_unique<GameplayMenu>(*this);
        menus[2] = std::make_unique<CreatorMenu>(*this);

        appRenderer->RenderWindow(*this);
    }

    void MenuHandler::ExitGame()
    {
        appRenderer->CloseWindow();
    }

    void MenuHandler::GetWindowSize(int& sizeX, int& sizeY)
    {
        appRenderer->GetWindowSize(sizeX, sizeY);
    }

    void MenuHandler::ExecuteMenuRender() { menus[activeMenu]->RenderMenu(); }
    
    void MenuHandler::ChangeMenu(int nextMenu) 
    {
        menus[activeMenu]->CloseMenu();
        menus[nextMenu]->OpenMenu();

        activeMenu = nextMenu; 
    }

    MenuHandler::MenuHandler() = default;
    MenuHandler::~MenuHandler() = default;
}