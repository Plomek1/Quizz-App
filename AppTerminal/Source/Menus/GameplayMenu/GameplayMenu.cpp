#include "GameplayMenu.h"
#include "SaveManager/SaveManager.h"
#include "../MenuHandler/MenuHandler.h"
#include "../MenuPrompts.h"

#include <iostream>
#include <optional>

namespace AppTerminal::MenuHandling::Gameplay
{
	std::optional<bool> AskQuestion(Core::Question& question, bool displayRepeatMessage);
	void PlayQuiz(Core::Quiz& quiz);
	void OpenQuizEndScreen(Core::Quiz& quiz, int score, int maxScore);
	void SelectQuiz(Core::Quiz& quiz);
	void DeleteQuiz(Core::Quiz& quiz);
	void OpenMainMenu();

	void DisplayQuizzes();
	bool HandleQuizSelection();

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
			ClearScreen();

			std::cout << GAMEPLAY_MENU_PROMPT << '\n';
			std::cout << GOTO_MAIN_MENU_PROMPT << '\n';

			if (loadExitCode == -1)
				std::cout << DATA_CORRUPTED_PROMPT << '\n';
			else if (quizzes.size() == 0)
				std::cout << NO_QUIZZES_PROMPT << '\n';
			else
				DisplayQuizzes();

			InvalidInputError(repeat);
			std::cout << '\n';

			repeat = !HandleQuizSelection();
		} while (repeat);
	}

	void DisplayQuizzes()
	{
		std::cout << '\n';
		for (int i = 0; i < quizzes.size(); i++)
			std::cout << PRESS_PROMPT << i + 1 << TO_SELECT_PROMPT << quizzes[i].title << '\n';
	}

	bool HandleQuizSelection()
	{
		std::string answer = GetPlayerInput();

		if (answer.length() == 1 && answer[0] == MAIN_MENU_OPTION)
		{
			OpenMainMenu();
			return true;
		}

		int quizIndex;
		if (ParsePlayerInputToInt(answer, quizIndex) && quizIndex > 0 && quizIndex <= quizzes.size())
		{
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
			ClearScreen();
			std::cout << DASHES_PROMPT << quiz.title << DASHES_PROMPT << "\n\n";
			std::cout << PLAY_PROMPT << '\n';
			std::cout << DELETE_PROMPT << '\n';
			std::cout << GO_BACK_PROMPT << '\n';

			InvalidInputError(repeat);
			std::cout << '\n';

			std::string answer = GetPlayerInput();
			std::unordered_map<char, std::function<void()>> actions;
			actions[PLAY_OPTION] = [&quiz]() { PlayQuiz(quiz); };							 //Play
			actions[DELETE_OPTION] = [&quiz]() { DeleteQuiz(quiz); OpenGameplayMenu(false); }; //Delete
			actions[GO_BACK_OPTION] = []()	     { OpenGameplayMenu(false); };                   //Go back

			repeat = !HandleSingleCharInput(answer, actions);
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
				ClearScreen();
				std::cout << DASHES_PROMPT << quiz.title << DASHES_PROMPT << "     " << score << '/' << maxScore << "\n\n";

				std::optional<bool> questionAnswer = AskQuestion(quiz.questions[i], repeat);
				if (questionAnswer != std::nullopt)
				{
					if (questionAnswer == true) score++;
					break;
				}

				repeat = true;

			} while (repeat);
		}
		OpenQuizEndScreen(quiz, score, maxScore);
	}

	void OpenQuizEndScreen(Core::Quiz& quiz, int score, int maxScore)
	{
		bool repeat = false;
		do
		{
			ClearScreen();
			std::cout << "Quiz is over!" << '\n' << "Your score: " << score << '/' << maxScore << "\n\n";
			std::cout << RETRY_PROMPT << '\n';
			std::cout << SELECT_ANOTHER_QUIZ_PROMPT << '\n';
			std::cout << GOTO_MAIN_MENU_PROMPT << '\n';

			InvalidInputError(repeat);
			std::cout << '\n';

			std::string answer = GetPlayerInput();
			std::unordered_map<char, std::function<void()>> actions;
			actions[RETRY_OPTION] = [&quiz]() { PlayQuiz(quiz); };		   //Retry
			actions[ANOTHER_QUIZ_OPTION] = []() { OpenGameplayMenu(false); }; //Select another quiz
			actions[MAIN_MENU_OPTION] = []() { OpenMainMenu(); };          //Main menu

			repeat = !HandleSingleCharInput(answer, actions);
		} while (repeat);
	}

	std::optional<bool> AskQuestion(Core::Question& question, bool displayRepeatMessage)
	{
		std::cout << question.title << '\n';

		for (int i = 0; i < question.answers.size(); i++)
			std::cout << i + 1 << ". " << question.answers[i] << '\n';

		InvalidInputError(displayRepeatMessage);
		std::cout << '\n';

		int answerIndex;
		if (GetPlayerIntInput(answerIndex) && answerIndex > 0 && answerIndex <= question.answers.size())
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
		MainMenu();
	}
}