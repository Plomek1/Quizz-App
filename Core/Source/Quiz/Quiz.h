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
	};

	//void to_json(nlohmann::json& j, Quiz& quiz)
	//{
	//	j = nlohmann::json{ {"title", quiz.title}, {"questions", quiz.questions} };
	//}

	//void from_json(nlohmann::json& j, Quiz& quiz)
	//{
	//	j.at("title").get_to(quiz.title);
	//	j.at("questions").get_to(quiz.questions);
	//}
}

