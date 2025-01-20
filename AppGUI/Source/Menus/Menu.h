#pragma once

#include <functional>

namespace AppGui
{
	class MenuHandler;
	typedef int ImGuiWindowFlags;

	class Menu
	{
	public: 
		virtual void OpenMenu() = 0;
		virtual void CloseMenu() = 0;
		virtual void RenderMenu() = 0;

	protected:
		Menu(MenuHandler& handler);
		
		void Exit(int nextMenu);
		MenuHandler& handler;
		ImGuiWindowFlags menuFlags;
	};
}

