#pragma once

#include <memory>

namespace AppGui
{
	class MainMenu;
	class GameplayMenu;

	class MenuHandler
	{
	public:
		MenuHandler();
		~MenuHandler();

		void StartGame();
		void ChangeMenu(int nextMenu);
	private:
		void RenderMenu();

		std::unique_ptr<MainMenu> mainMenu;
		std::unique_ptr<GameplayMenu> gameplayMenu;

		int activeMenu = 0;

	};
}

