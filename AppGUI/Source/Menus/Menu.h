#pragma once

#include "MenuHandler.h"

#include <functional>

namespace AppGui
{
	class Menu
	{
	public: 
		virtual void RenderMenu() = 0;

	protected:
		Menu(MenuHandler& handler) : handler(handler) {};
		
		inline void Exit(int nextMenu) { handler.ChangeMenu(nextMenu); }
		MenuHandler& handler;
	};
}

