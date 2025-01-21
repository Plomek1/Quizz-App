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
		void ExitQuiz();

		void RenderQuizSelection();
		void RenderQuizGameplay();

		std::vector<Core::Quiz> quizzes;
		
		struct ActiveQuiz
		{
			Core::Quiz* quiz = nullptr;
			unsigned int score = 0;
			unsigned int currentQuestion = 0;
		};

		bool playingQuiz = false;
		ActiveQuiz activeQuiz;
	};
}

