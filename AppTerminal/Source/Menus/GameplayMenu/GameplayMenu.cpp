#include "GameplayMenu.h"
#include "SaveManager/SaveManager.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>
#include <optional>

namespace AppTerminal::MenuHandling::Gameplay
{
	std::optional<bool> AskQuestion(Core::Question& question, bool displayRepeatMessage);
	void PlayQuiz(Core::Quiz& quiz);
	void SelectQuiz(Core::Quiz& quiz);
	void DeleteQuiz(Core::Quiz& quiz);
	void OpenMainMenu();

	void DisplayQuizzes();
	bool HandleQuizSelection();
	bool HandleEndScreenSelection(Core::Quiz& quiz);
	
	std::vector<Core::Quiz> quizzes;
	bool quizDeleted;
	
	void OpenGameplayMenu(bool loadQuizzesFromFile)
	{

		int loadExitCode = 0; 
		if (loadQuizzesFromFile)
		{
			quizzes.clear();
			Core::LoadQuizzes(quizzes);
			quizDeleted = false;
		}

		bool repeat = false;

		do {
			MenuHandling::ClearScreen();

			std::cout << "-----Gameplay Menu-----\n";
			std::cout << "Press M to go to main menu\n";

			if (loadExitCode == -1)
				std::cout << "\nSave data is corrupted!\n";
			else if (quizzes.size() == 0)
				std::cout << "\nNo quizzes available, please create a quiz first!\n";
			else
				DisplayQuizzes();

			MenuHandling::InvalidInputError(repeat);
			std::cout << '\n';

			repeat = !HandleQuizSelection();
		} while (repeat);
	}

	void DisplayQuizzes()
	{
		std::cout << '\n';
		for (int i = 0; i < quizzes.size(); i++)
			std::cout << "Press " << i + 1 << " to select " << quizzes[i].title << '\n';
	}

	bool HandleQuizSelection()
	{
		std::string answer = MenuHandling::GetPlayerInput();

		if (answer.length() == 1 && answer[0] == 'm')
		{
			OpenMainMenu();
			return true;
		}

		int quizIndex;
		if (MenuHandling::ParsePlayerInputToInt(answer, quizIndex))
		{
			if (quizIndex > quizzes.size() || quizIndex <= 0)
				return false;

			SelectQuiz(quizzes[quizIndex - 1]);
			return true;
		}

		return false;
	}

	void SelectQuiz(Core::Quiz& quiz)
	{
		bool repeat = false;
		
		do
		{
			MenuHandling::ClearScreen();
			std::cout << "-----" << quiz.title << "-----" << "\n\n";
			std::cout << "Press P to play" << '\n';
			std::cout << "Press D to go delete" << '\n';
			std::cout << "Press B to go back" << '\n';

			MenuHandling::InvalidInputError(repeat);
			std::cout << '\n';

			std::string answer = MenuHandling::GetPlayerInput();

			if (answer.length() == 1)
			{
				switch (answer[0])
				{
				case 'p': //Play
					PlayQuiz(quiz);
					return;

				case 'd': //Delete
					DeleteQuiz(quiz);
					OpenGameplayMenu(false);
					return;

				case 'b': //Go back
					OpenGameplayMenu(false);
					return;
				}
			}
			repeat = true;
		} while (repeat);
	}

	void PlayQuiz(Core::Quiz& quiz)
	{
		int score = 0;
		int maxScore = quiz.questions.size();

		for (int i = 0; i < maxScore; i++)
		{
			bool repeat = false;

			do
			{
				MenuHandling::ClearScreen();
				std::cout << "-----" << quiz.title << "-----     " << score << '/' << maxScore << "\n\n";

				std::optional<bool> questionAnswer = AskQuestion(quiz.questions[i], repeat);

				
				if (questionAnswer != std::nullopt)
				{
					if (questionAnswer == true) score++;
					break;
				}

				repeat = true;

			} while (repeat);
		}

		bool repeat = false;

		do
		{
			MenuHandling::ClearScreen();
			std::cout << "Quiz is over!" << '\n' << "Your score: " << score << '/' << maxScore << "\n\n";
			std::cout << "Press R to try again" << '\n';
			std::cout << "Press S to select another quiz" << '\n';
			std::cout << "Press M to go to main menu" << '\n';

			MenuHandling::InvalidInputError(repeat);
			std::cout << '\n';

			

			repeat = !HandleEndScreenSelection(quiz);
		} while (repeat);
	}

	bool HandleEndScreenSelection(Core::Quiz& quiz)
	{
		std::string answer = MenuHandling::GetPlayerInput();
		if (answer.size() == 1)
		{
			switch (answer[0])
			{
			case 'r': //Retry
				PlayQuiz(quiz);
				return true;
			case 's': //Select another quiz
				OpenGameplayMenu(false);
				return true;
			case 'm': //Main menu
				OpenMainMenu();
				return true;
			}
		}
		return false;
	}

	std::optional<bool> AskQuestion(Core::Question& question, bool displayRepeatMessage)
	{
		std::cout << question.title << '\n';

		for (int i = 0; i < question.answers.size(); i++)
			std::cout << i + 1 << ". " << question.answers[i] << '\n';

		MenuHandling::InvalidInputError(displayRepeatMessage);
		std::cout << '\n';

		int answerIndex;
		if (MenuHandling::GetPlayerIntInput(answerIndex) && answerIndex > 0 && answerIndex <= question.answers.size())
			return answerIndex -1 == question.correctAnswerIndex;
		
		return std::nullopt;
	}

	void DeleteQuiz(Core::Quiz& quiz)
	{
		for (int i = 0; i < quizzes.size(); i++)
		{
			if (&quizzes[i] == &quiz)
			{
				quizzes.erase(quizzes.begin() + i);
				break;
			}
		}

		quizDeleted = true;
	}

	void OpenMainMenu()
	{
		if (quizDeleted)
			Core::SaveQuizzes(quizzes);
		MenuHandling::MainMenu();
	}
}