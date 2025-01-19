#pragma once

#include "Menu.h"

namespace AppGui
{
	class GameplayMenu : public Menu
	{
	public:
		GameplayMenu(MenuHandler& handler) : Menu(handler) {}
		void RenderMenu() override;
	};
}

