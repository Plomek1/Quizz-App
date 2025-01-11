#include "GameplayMenu.h"
#include "QuizLoader/QuizLoader.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

bool AskQuestion(Question &question, bool &answerCorrect, bool displayRepeatMessage);
void PlayQuiz(Quiz &quiz);

void OpenGameplayMenu()
{
	std::vector<Quiz> quizzes = LoadQuizzes();

	bool repeat = false;

	do {
		ClearScreen();

		std::cout << "-----Gameplay Menu-----\n";
		std::cout << "Press M to go to main menu\n";

		if (quizzes.size() == 0)
			std::cout << "\nNo quizzes available, please create a quiz first!\n";
		else
		{
			std::cout << '\n';
			for (int i = 0; i < quizzes.size(); i++)
				std::cout << "Press " << i + 1 << " to play " << quizzes[i].title << '\n';
		}

		if (repeat)
			std::cout << "\nPlease enter correct option\n";
		std::cout << '\n';

		std::string answer = GetPlayerInput();

		if (answer.length() == 1)
		{
			switch (answer[0])
			{
			case 'm': //Main menu
				MainMenu();
				return;
			}
		}

		int quizIndex;
		if (ParsePlayerInputToInt(answer, quizIndex))
		{
			if (quizIndex > quizzes.size())
			{
				repeat = true;
				continue;
			}

			PlayQuiz(quizzes[quizIndex - 1]);
			return;
		}

		repeat = true;
	} while (repeat);
}

void PlayQuiz(Quiz& quiz)
{
	int score = 0;
	int maxScore = quiz.questions.size();

	for (int i = 0; i < maxScore; i++)
	{
		bool repeat = false;

		do
		{
			ClearScreen();
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

	ClearScreen();
	std::cout << "Quiz is over!" << '\n' << "Your score: " << score << '/' << maxScore << "\n\n" << "Press enter to continue...";
	std::cin.ignore();
	std::cin.get();
	MainMenu();
}

bool AskQuestion(Question &question, bool &answerCorrect, bool displayRepeatMessage)
{
	std::cout << question.title << '\n';

	for (int i = 0; i < question.answers.size(); i++)
		std::cout << i + 1 << ". " << question.answers[i] << '\n';

	if(displayRepeatMessage)
		std::cout << "\nPlease enter correct option\n";
	std::cout << '\n';

	int answerIndex;
	if (GetPlayerIntInput(answerIndex))
	{
		if (answerIndex > question.answers.size())
			return false;

		answerCorrect = answerIndex - 1 == question.correctAnswerIndex;
		return true;
	}
	return false;
}
