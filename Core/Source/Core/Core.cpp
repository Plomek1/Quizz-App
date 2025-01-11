#include "Core.h"
#include "Question/Question.h"

#include <iostream>

#include <vector>

namespace Core {

	Question* q;

	void PrintText(const char* text)
	{
		std::cout << text << '\n';
		std::cin.get();
	}

	void CreateQuestion()
	{
		std::vector<const char*> a;
		a.push_back("Answer 1");
		a.push_back("Answer 2");
		a.push_back("Answer 3");
		a.push_back("Answer 4");
		q = new Question("Test", &a, 1);
	}

	void PrintQuestion()
	{
		std::cout << q->title << '\n';
		std::cout << q->answers[0] << '\n';
		std::cout << q->answers[1] << '\n';
		std::cout << q->answers[2] << '\n';
		std::cout << q->answers[3] << '\n';
		std::cout << "Correct: " << q->answers[q->correctAnswerIndex] << '\n';
		std::cin.get();
	}
}