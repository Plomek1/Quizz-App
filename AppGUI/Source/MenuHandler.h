#pragma once

#include <memory>
#include <vector>

namespace AppGui
{
	class Menu;

	class MenuHandler
	{
	public:
		MenuHandler();
		~MenuHandler();

		void StartGame();

		void ExecuteMenuRender();
		void ChangeMenu(int nextMenu);

	private:
		std::vector<std::unique_ptr<Menu>> menus;
		int activeMenu = 0;
	};
}

