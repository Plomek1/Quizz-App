#pragma once

#include "Question.h"

namespace Core
{
	struct Quiz
	{
	public:
		std::string title;
		std::vector<Question> questions;

		Quiz(std::string title, std::vector<Question>* questions)
		{
			this->title = title;
			this->questions = *questions;
		}

		Quiz() 
		{
			this->title = "";
			this->questions = std::vector<Question>{ Question() };
		}
	};
}

