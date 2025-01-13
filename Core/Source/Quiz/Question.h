#pragma once

#include <vector>
#include <string>

namespace Core
{
	struct Question
	{
	public:
		std::string title;
		std::vector<std::string> answers;
		int correctAnswerIndex;

		Question(std::string title, std::vector<std::string>* answers, int correctAnswerIndex)
		{
			this->title = title;
			this->answers = *answers;
			this->correctAnswerIndex = correctAnswerIndex;
		}
	};
	
	//void to_json(nlohmann::json& j, Question& question)
	//{
	//	j = nlohmann::json{ {"title", question.title}, {"correctAnswerIndex", question.correctAnswerIndex}, { "answers", question.answers }};
	//}

	//void from_json(nlohmann::json j, Question& question)
	//{
	//	j.at("title").get_to(question.title);
	//	j.at("correctAnswerIndex").get_to(question.correctAnswerIndex);
	//	j.at("answers").get_to(question.answers);
	//}
}