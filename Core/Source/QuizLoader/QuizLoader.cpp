#include "QuizLoader.h"

#include<string>
#include <nlohmann/json.hpp>

#include <shlobj.h>
#include <iostream>

namespace Core
{
	bool GetDocumentsPath(std::string& documentsPath);

	bool LoadQuizzes(std::vector<Quiz> &quizList)
	{
		//Simulating reading from json

		std::string documentsPath;
		if (!GetDocumentsPath(documentsPath))
			return false;

		std::cout << documentsPath;


		for (int i = 1; i <= 3; i++)
		{
			std::vector<Question> questions;

			for (int j = 1; j <= 5; j++)
			{
				std::string qName = "Question " + std::to_string(j);
				questions.push_back(Question(qName.c_str(), new std::vector<std::string>{ "Answer 1", "Answer 2", "Answer 3", "Answer 4" }, 0));
			}
			std::string qName = "Quiz " + std::to_string(i);
			quizList.push_back(Quiz(qName.c_str(), &questions));
		}

		return true;
	}

	//https://stackoverflow.com/questions/2414828/get-path-to-my-documents
	//https://stackoverflow.com/questions/6006319/converting-tchar-to-string-in-c
	bool GetDocumentsPath(std::string &documentsPath)
	{
		TCHAR path[MAX_PATH];
		
		HRESULT result = SHGetFolderPath(NULL, CSIDL_COMMON_DOCUMENTS, NULL, SHGFP_TYPE_CURRENT, path);

		if (result != S_OK)
		{
			std::cout << "Error while trying to get Documents path: " << result << '\n';
			return false;
		}

		std::wstring wstring(path);
		documentsPath = std::string(wstring.begin(), wstring.end());
		return true;
	}
}
