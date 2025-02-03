#include "CreatorMenu.h"

#include "MenuHandler.h"
#include "SaveManager/SaveManager.h"

#include <imgui.h>
#include <vector>
#include <iostream>

namespace AppGui
{
	const int MAX_INPUT_LENGTH = 64;

	void CreatorMenu::RenderMenu()
	{
		bool p_open; 
		ImGui::Begin("Editor", &p_open, menuFlags);

		int sizeX, sizeY;
		ImGui::SetWindowPos(ImVec2(0, 0));
		handler.GetWindowSize(sizeX, sizeY);
		ImGui::SetWindowSize(ImVec2(sizeX, sizeY));

		char titleBuffer[MAX_INPUT_LENGTH];
		strcpy(titleBuffer, quiz.title.c_str());
		ImGui::InputText("Title", titleBuffer, MAX_INPUT_LENGTH);
		quiz.title = titleBuffer;

		RenderQuestions();

		if (ImGui::Button("Save quiz") && SaveQuiz())
			handler.ChangeMenu(0);

		if (ImGui::Button("Main Menu"))
			handler.ChangeMenu(0);

		ImGui::End();
	}

	void CreatorMenu::RenderQuestions()
	{
		for (int i = 0; i < quiz.questions.size(); i++)
			RenderQuestionAnswers(quiz.questions[i], i);

		if (ImGui::Button("Add new question"))
			quiz.questions.push_back(Core::Question());
	}

	void CreatorMenu::RenderQuestionAnswers(Core::Question& question, int questionIndex)
	{
		char title[MAX_INPUT_LENGTH];
		strcpy(title, question.title.c_str());

		std::string questionLabel = "Question " + std::to_string(questionIndex+1);
		ImGui::InputText(questionLabel.c_str(), title, MAX_INPUT_LENGTH);
		question.title = title;

		for (int i = 0; i < question.answers.size(); i++)
		{
			char answer[MAX_INPUT_LENGTH];
			strcpy(answer, question.answers[i].c_str());

			std::string answerLabel = "Answer " + std::to_string(i+1) + "##" + std::to_string(questionIndex);
			ImGui::InputText(answerLabel.c_str(), answer, MAX_INPUT_LENGTH);
			question.answers[i] = answer;
		}

		std::string buttonLabel = "Add new answer##" + std::to_string(questionIndex);
		if (ImGui::Button(buttonLabel.c_str()))
			question.answers.push_back(std::string());

		std::string sliderLabel = "Correct answer##" + std::to_string(questionIndex);
		int correctAnswer = question.correctAnswerIndex + 1;
		ImGui::SliderInt(sliderLabel.c_str(), &correctAnswer, 1, question.answers.size());
		question.correctAnswerIndex = correctAnswer - 1;
	}

	bool CreatorMenu::SaveQuiz()
	{
		//Looking for empty fields
		if (quiz.title.length() == 0) return false;
		for (Core::Question& question : quiz.questions)
		{
			if (question.title.length() == 0) return false;
			for (std::string& answer : question.answers)
				if (answer.length() == 0) return false;
		}

		//Saving new quiz
		std::vector<Core::Quiz> quizzes;
		Core::LoadQuizzes(quizzes);
		quizzes.push_back(quiz);
		Core::SaveQuizzes(quizzes);
	}

	void CreatorMenu::OpenMenu() { quiz = Core::Quiz(); }

}
