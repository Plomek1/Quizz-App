#include "Question.h"

#include <iostream>

Question::Question(std::string title, std::vector<std::string>* answers, int correctAnswerIndex)
{
	this->title = title;
	this->answers = *answers;
	this->correctAnswerIndex = correctAnswerIndex;
}