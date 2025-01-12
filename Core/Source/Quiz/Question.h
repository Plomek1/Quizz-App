#pragma once

#include <string>
#include <vector>

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
}