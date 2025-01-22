#pragma once

#include "Menu.h"

#include "Quiz/Quiz.h"

namespace AppGui
{
	class CreatorMenu : public Menu
	{
	public:
		CreatorMenu(MenuHandler& handler) : Menu(handler) {}

		void OpenMenu() override;
		void CloseMenu() override {};
		void RenderMenu() override;

	private:
		void RenderQuestions();
		void RenderQuestionAnswers(Core::Question& question, int questionIndex);

		bool SaveQuiz();

		Core::Quiz quiz;

	};


}

