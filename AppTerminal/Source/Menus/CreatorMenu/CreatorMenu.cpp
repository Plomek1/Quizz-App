#include "CreatorMenu.h"
#include "../MenuHandler/MenuHandler.h"
#include "../MenuPrompts.h"
#include "SaveManager/SaveManager.h"

#include <iostream>

namespace AppTerminal::MenuHandling::Creator
{
	Core::Quiz CreateNewQuiz(std::string & title);
	Core::Question AddNewQuestion();
	std::vector<std::string> AddAnswers(int answerCount);

	void OpenCreatorMenu()
	{
		bool repeat = false;
		do
		{
			ClearScreen();

			std::cout << CREATOR_MENU_PROMPT << '\n';
			std::cout << GOTO_MAIN_MENU_PROMPT << '\n';
			std::cout << '\n' << ENTER_QUIZ_TITLE_PROMPT << '\n';

			InvalidInputError(repeat);
			std::cout << '\n';

			std::string answer = GetPlayerInput();
			
			if (answer == "m")
			{
				MainMenu();
				return;
			}

			Core::Quiz newQuiz = CreateNewQuiz(answer);

			//Save new quiz
			std::vector<Core::Quiz> quizzes;
			Core::LoadQuizzes(quizzes);
			quizzes.push_back(newQuiz);
			Core::SaveQuizzes(quizzes);

			MainMenu();

			repeat = true;

		} while (repeat);
	}

	Core::Quiz CreateNewQuiz(std::string& title)
	{
		std::vector<Core::Question> questions;
		
		bool addQuestion = true;
		while (true)
		{
			if (addQuestion)
			{
				questions.push_back(AddNewQuestion());
				addQuestion = false;
			}

			bool repeat = false;
			do
			{
				ClearScreen();

				std::cout << ADD_NEW_QUESTION_PROMPT << '\n';
				std::cout << SAVE_QUIZ_PROMPT << '\n';
				InvalidInputError(repeat);
				std::cout << '\n';

				std::string answer = GetPlayerInput();

				if (answer.length() != 1)
				{
					repeat = true;
					continue;
				}

				if (answer[0] == ADD_NEW_QUESTION_OPTION)
				{
					addQuestion = true;
					continue;
				}

				if (answer[0] == SAVE_QUIZ_OPTION)
					return Core::Quiz(title, &questions);

				repeat = true;
			} while (repeat);
		}
	}

	Core::Question AddNewQuestion()
	{
		ClearScreen();
		std::cout << ENTER_QUESTION_TITLE_PROMPT << "\n\n";
		std::string title = GetPlayerInput();
		std::vector<std::string> answers;
		int correctAnswerIndex;

		bool repeat = false;
		do 
		{
			ClearScreen();

			std::cout << ENTER_ANSWER_COUNT_PROMPT << '\n';
			InvalidInputError(repeat);
			std::cout << '\n';

			int answerCount;
			if (GetPlayerIntInput(answerCount))
			{
				answers = AddAnswers(answerCount);
				break;
			}

			repeat = true;
		} while (repeat);

		repeat = false;
		do
		{
			ClearScreen();

			std::cout << ENTER_CORRECT_ANSWER_INDEX_PROMPT << '\n';
			InvalidInputError(repeat);
			std::cout << '\n';

			if (GetPlayerIntInput(correctAnswerIndex))
			{
				if (correctAnswerIndex > 0 && correctAnswerIndex <= answers.size())
				{
					correctAnswerIndex--;
					break;
				}
			}

			repeat = true;
		} while (repeat);

		return Core::Question(title, &answers, correctAnswerIndex);
	}

	std::vector<std::string> AddAnswers(int answerCount)
	{
		std::vector<std::string> answers(answerCount);

		for (int i = 0; i < answerCount; i++)
		{
			ClearScreen();

			std::cout << ENTER_ANSWER_PROMPT << i + 1 << ":\n\n";
			answers[i] = GetPlayerInput();
		}
		return answers;
	}
}