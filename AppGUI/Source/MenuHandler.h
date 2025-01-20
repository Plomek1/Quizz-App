#pragma once

#include <memory>
#include <vector>

namespace AppGui
{
	class Menu;
	class AppRenderer;

	class MenuHandler
	{
	public:
		MenuHandler();
		~MenuHandler();

		void StartGame();
		void ExitGame();

		void GetWindowSize(int& sizeX, int& sizeY);

		void ExecuteMenuRender();
		void ChangeMenu(int nextMenu);

	private:
		std::unique_ptr<AppRenderer> appRenderer;
		std::vector<std::unique_ptr<Menu>> menus;
		int activeMenu = 0;
	};
}

