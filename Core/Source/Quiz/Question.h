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

		Question() 
		{
			this->title = "";
			this->answers = std::vector<std::string>{ "" };
			this->correctAnswerIndex = 0;
		};
	};
}