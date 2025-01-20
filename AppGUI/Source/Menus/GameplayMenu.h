#pragma once

#include "Menu.h"
#include <Quiz/Quiz.h>

#include <vector>

namespace AppGui
{
	class GameplayMenu : public Menu
	{
	public:
		GameplayMenu(MenuHandler& handler) : Menu(handler) {}

		void OpenMenu() override;
		void CloseMenu() override;
		void RenderMenu() override;

	private:
		void PlayQuiz(Core::Quiz& quiz);

		std::vector<Core::Quiz> quizzes;
	};
}

