#pragma once

#include "Question/Question.h"


class Quiz
{
public:
	std::string title;
	std::vector<Question> questions;
	Quiz(std::string title, std::vector<Question>* questions);
};

