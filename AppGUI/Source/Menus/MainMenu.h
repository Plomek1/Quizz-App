#pragma once

#include "Menu.h"

class MenuHandler;

namespace AppGui {

	class MainMenu : public Menu
	{
	public:
		MainMenu(MenuHandler& handler) : Menu(handler) {}
		void RenderMenu() override;

	private:
		bool show_demo_window = true;
		bool show_another_window = true;
	};
}

