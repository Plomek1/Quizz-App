#include "Quiz.h"

Quiz::Quiz(std::string title, std::vector<Question>* questions)
{
	this->title = title;
	this->questions = *questions;
}