#include "GameplayMenu.h"
#include "SaveManager/SaveManager.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

namespace AppTerminal::MenuHandling::Gameplay
{
	bool AskQuestion(Core::Question& question, bool& answerCorrect, bool displayRepeatMessage);
	void PlayQuiz(Core::Quiz& quiz);
	void SelectQuiz(Core::Quiz& quiz);
	void DeleteQuiz(Core::Quiz& quiz);
	void OpenMainMenu();
	
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
			{
				std::cout << '\n';
				for (int i = 0; i < quizzes.size(); i++)
					std::cout << "Press " << i + 1 << " to select " << quizzes[i].title << '\n';
			}

			if (repeat)
				std::cout << "\nInvalid input, please try again\n";
			std::cout << '\n';

			std::string answer = MenuHandling::GetPlayerInput();

			if (answer.length() == 1 && answer[0] == 'm')
			{
				OpenMainMenu();
				return;
			}

			int quizIndex;
			if (MenuHandling::ParsePlayerInputToInt(answer, quizIndex))
			{
				if (quizIndex > quizzes.size() || quizIndex <= 0)
				{
					repeat = true;
					continue;
				}

				SelectQuiz(quizzes[quizIndex - 1]);
				return;
			}

			repeat = true;
		} while (repeat);
	}

	void SelectQuiz(Core::Quiz& quiz)
	{
		bool repeat = false;
		
		do
		{
			MenuHandling::ClearScreen();
			std::cout << "-----" << quiz.title << "-----" << "\n\n";
			std::cout << "Press p to play" << '\n';
			std::cout << "Press d to go delete" << '\n';
			std::cout << "Press b to go back" << '\n';

			if (repeat)
				std::cout << "\nInvalid input, please try again\n";
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

				bool answerCorrect;
				if (AskQuestion(quiz.questions[i], answerCorrect, repeat))
				{
					if (answerCorrect) score++;
					break;
				}

				repeat = true;
			} while (repeat);
		}

		MenuHandling::ClearScreen();
		std::cout << "Quiz is over!" << '\n' << "Your score: " << score << '/' << maxScore << "\n\n" << "Press enter to continue...";
		std::cin.ignore();
		std::cin.get();

		OpenMainMenu();
	}

	bool AskQuestion(Core::Question& question, bool& answerCorrect, bool displayRepeatMessage)
	{
		std::cout << question.title << '\n';

		for (int i = 0; i < question.answers.size(); i++)
			std::cout << i + 1 << ". " << question.answers[i] << '\n';

		if (displayRepeatMessage)
			std::cout << "\nInvalid input, please try again\n";
		std::cout << '\n';

		int answerIndex;
		if (MenuHandling::GetPlayerIntInput(answerIndex))
		{
			if (answerIndex > question.answers.size() || answerIndex <= 0)
				return false;

			answerCorrect = answerIndex - 1 == question.correctAnswerIndex;
			return true;
		}
		return false;
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