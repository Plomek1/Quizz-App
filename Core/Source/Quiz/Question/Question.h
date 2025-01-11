#pragma once

#include <string>
#include <vector>

class Question
{
public: 
	std::string title;
	std::vector<std::string> answers;
	int correctAnswerIndex;

	Question(std::string question, std::vector<std::string>* answers, int correctAnswerIndex);
};

