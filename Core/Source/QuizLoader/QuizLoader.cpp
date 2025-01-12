#include "QuizLoader.h"
#include "../SaveManager/SaveManager.h"

#include <iostream>

namespace Core
{
	bool LoadQuizzesLoader(std::vector<Quiz> &quizList)
	{
		std::string documentsPath;

		Quiz test = Quiz("test", new std::vector<Question>);
		SaveQuiz(test);

		std::cout << documentsPath;


		for (int i = 1; i <= 3; i++)
		{
			std::vector<Question> questions;

			for (int j = 1; j <= 5; j++)
			{
				std::string qName = "Question " + std::to_string(j);
				questions.push_back(Question(qName.c_str(), new std::vector<std::string>{ "Answer 1", "Answer 2", "Answer 3", "Answer 4" }, 0));
			}
			std::string qName = "Quiz " + std::to_string(i);
			quizList.push_back(Quiz(qName.c_str(), &questions));
		}

		return true;
	}
}
