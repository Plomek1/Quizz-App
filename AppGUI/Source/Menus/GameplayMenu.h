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
		void SelectQuiz(Core::Quiz& quiz);
		void StartQuiz();
		void ExitQuiz();

		void DeleteQuiz(Core::Quiz& quiz);

		void RenderQuizList();
		void RenderSelectedQuiz();
		void RenderPlayedQuiz();

		std::vector<Core::Quiz> quizzes;
		bool quizDeleted = false;
		
		struct ActiveQuiz
		{
			Core::Quiz* quiz = nullptr;
			unsigned int score = 0;
			unsigned int currentQuestion = 0;
		};

		enum menuState
		{
			LIST,
			SELECTED,
			PLAYING
		};

		menuState menuState = LIST;
		ActiveQuiz activeQuiz;
	};
}

