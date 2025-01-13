#include "SaveManager.h"

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <shlobj.h>

namespace Core
{
	bool ConvertQuizzesToJson(std::vector<Quiz>& quizzes, nlohmann::json& json)
	{
		for (int i = 0; i < quizzes.size(); i++)
		{

			std::vector<nlohmann::json> questionsJson;
			try 
			{
				for (int j = 0; j < quizzes[i].questions.size(); j++)
				{
					nlohmann::json questionJson;

						questionJson["title"] = quizzes[i].questions[j].title;
						questionJson["correctAnswerIndex"] = quizzes[i].questions[j].correctAnswerIndex;
						questionJson["answers"] = quizzes[i].questions[j].answers;

					questionsJson.push_back(questionJson);
				}

				nlohmann::json quizJson;

				quizJson["questions"] = questionsJson;
				quizJson["title"] = quizzes[i].title;
				json.push_back(quizJson);
			}
			catch (std::exception ex) { return false; }
		}

		return true;
	}

	bool ConvertJsonToQuizzes(std::vector<Quiz>& quizzes, nlohmann::json& json)
	{
		for (int i = 0; i < json.size(); i++)
		{
			try
			{
				std::string title = json[i]["title"].template get<std::string>();
				std::vector<Question> questions;

				for (int j = 0; j < json[i]["questions"].size(); j++)
				{
					std::string title = json[i]["questions"][j]["title"].template get<std::string>();
					std::vector<std::string> answers = json[i]["questions"][j]["answers"].template get<std::vector<std::string>>();
					int correctAnswerIndex = json[i]["questions"][j]["correctAnswerIndex"].template get<int>();

					questions.push_back(Question(title, &answers, correctAnswerIndex));
				}

				quizzes.push_back(Quiz(title, &questions));

			}
			catch (std::exception ex) { return false; }
		}

		return true;
	}

	int LoadQuizzes(std::vector<Quiz>& quizzes)
	{
		std::string documentsPath;
		if (!GetDocumentsPath(documentsPath)) return -1;

		std::string filePath = documentsPath + "\\QuizzApp\\quizzes.json";

		std::ifstream saveFile(filePath);
		if (!saveFile.is_open()) return 0;

		std::stringstream buffer;
		buffer << saveFile.rdbuf();

		nlohmann::json saveJson;
		try {
			saveJson = nlohmann::json::parse(buffer);
		}
		catch (std::exception ex) { return -1; }

		if(!ConvertJsonToQuizzes(quizzes, saveJson)) return -1;
		
		return 1;
	}

	bool SaveQuizzes(std::vector<Quiz>& quizzes)
	{
		std::string documentsPath;
		if (!GetDocumentsPath(documentsPath)) return false;

		std::string folderPath = documentsPath + "\\QuizzApp";
		std::string filePath = folderPath +"\\quizzes.json";
		
		if (!std::filesystem::is_directory(folderPath))
			std::filesystem::create_directory(folderPath);

		std::ofstream saveFile(filePath);
		nlohmann::json saveJson;

		ConvertQuizzesToJson(quizzes, saveJson);
		saveFile << saveJson;

		saveFile.close();

		return true;
	}

	//https://stackoverflow.com/questions/2414828/get-path-to-my-documents
	//https://stackoverflow.com/questions/6006319/converting-tchar-to-string-in-c
	bool GetDocumentsPath(std::string& documentsPath)
	{
		TCHAR path[MAX_PATH];
		
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, path);

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