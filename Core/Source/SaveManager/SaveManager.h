#pragma once

#include <Quiz/Quiz.h>


namespace Core
{
	int LoadQuizzes(std::vector<Quiz>& quizzes);
	bool SaveQuizzes(std::vector<Quiz>& quizzes);
	bool GetDocumentsPath(std::string& documentsPath);
}