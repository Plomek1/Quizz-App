#pragma once

#include <vector>

class Question
{
public: 
	const char* title;
	std::vector<const char*> answers;
	int correctAnswerIndex;

	Question(const char* question, std::vector<const char*>* answers, int correctAnswerIndex);
};

