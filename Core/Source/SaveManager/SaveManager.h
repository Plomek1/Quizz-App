#pragma once

#include <vector>
#include <Quiz/Quiz.h>


namespace Core
{
	bool LoadQuizzes(std::vector<Quiz>& quizzes);
	bool SaveQuiz(Quiz& quiz);
	bool GetDocumentsPath(std::string& documentsPath);
}