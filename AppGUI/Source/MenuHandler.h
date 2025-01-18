#pragma once

namespace AppGUI
{
	class MenuHandler
	{
	public:
		void ChangeMenu(int newMenu);
		void RenderMenu();
	private:
		int activeMenu;
	};
}

