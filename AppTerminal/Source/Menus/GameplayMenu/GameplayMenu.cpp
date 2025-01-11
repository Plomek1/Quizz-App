#include "GameplayMenu.h"
#include "QuizLoader/QuizLoader.h"
#include "../MenuHandler/MenuHandler.h"

#include <iostream>

void PrintQuizQuestion(Question &question);
void OpenQuiz(Quiz &quiz);

void OpenGameplayMenu()
{
	std::vector<Quiz> quizzes = LoadQuizzes();

	bool repeat = false;

	while (true)
	{
		ClearScreen();

		std::cout << "-----Gameplay Menu-----\n";
		std::cout << "Press M to go to main menu\n";

		if (quizzes.size() == 0)
			std::cout << "\nNo quizzes available, please create a quiz first!\n";
		else
		{
			std::cout << '\n';
			for (int i = 0; i < quizzes.size(); i++)
				std::cout << "Press " << i+1 << " to play " << quizzes[i].title << '\n';
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
		try 
		{
			int quizIndex = std::stoi(answer);
			if (quizIndex > quizzes.size())
			{
				repeat = true;
				continue;
			}

			OpenQuiz(quizzes[quizIndex - 1]);
			return;
		}
		catch (const std::invalid_argument& e) { }

		repeat = true;
	}

}

void OpenQuiz(Quiz& quiz)
{
	ClearScreen();
	std::cout << quiz.title << '\n';
	PrintQuizQuestion(quiz.questions[0]);
}

void PrintQuizQuestion(Question& question)
{
	std::cout << question.title << '\n';
	std::cout << question.answers[0] << '\n';
	std::cout << question.answers[1] << '\n';
	std::cout << question.answers[2] << '\n';
	std::cout << question.answers[3] << '\n';
	std::cout << "Correct: " << question.answers[question.correctAnswerIndex] << '\n';
	std::cin.get();
}
