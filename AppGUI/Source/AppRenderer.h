#pragma once

struct GLFWwindow;

namespace AppGui
{
	class MenuHandler;

	class AppRenderer
	{

	public:
		void RenderWindow(MenuHandler& handler);
		void CloseWindow();

		void GetWindowSize(int& sizeX, int& sizeY);

	private:
		GLFWwindow* window;
	};
}