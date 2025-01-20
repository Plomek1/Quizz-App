#pragma once

#include "Menu.h"

class MenuHandler;

namespace AppGui 
{
	class MainMenu : public Menu
	{
	public:
		MainMenu(MenuHandler& handler) : Menu(handler) {}
		
		void OpenMenu() override {}
		void CloseMenu() override {}
		void RenderMenu() override;
	};
}

