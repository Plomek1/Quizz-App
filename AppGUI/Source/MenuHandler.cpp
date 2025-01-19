#include "MenuHandler.h"

#include "AppRenderer.h"

#include "Menus/MainMenu.h"
#include "Menus/GameplayMenu.h"

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

    void MenuHandler::ExecuteMenuRender() { menus[activeMenu]->RenderMenu(); }
    void MenuHandler::ChangeMenu(int nextMenu) { activeMenu = nextMenu; }

    MenuHandler::MenuHandler() = default;
    MenuHandler::~MenuHandler() = default;
}