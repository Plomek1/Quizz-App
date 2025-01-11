#include "Question.h"

#include <iostream>

Question::Question(const char* title, std::vector<const char*>* answers, int correctAnswerIndex)
{
	this->title = title;
	this->answers = *answers;
	this->correctAnswerIndex = correctAnswerIndex;
	std::cout << "qqqq";
}