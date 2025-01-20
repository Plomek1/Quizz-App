#include "Menu.h"

#include "MenuHandler.h"
#include <imgui.h>

namespace AppGui
{
	Menu::Menu(MenuHandler& handler) : handler(handler),
		menuFlags(menuFlags = ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove) {}

	void Menu::Exit(int nextMenu) { handler.ChangeMenu(nextMenu); }

}
