#include "SaveManager.h"

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <shlobj.h>

namespace Core
{
	bool LoadQuizzes(std::vector<Quiz>& quizzes)
	{
		return true;
	}

	bool SaveQuiz(Quiz& quizzes)
	{
		
		std::string documentsPath;
		if (!GetDocumentsPath(documentsPath)) return false;


		std::string folderPath = documentsPath + "\\QuizzApp";
		std::string filePath = folderPath +"\\quizzes.json";
		
		if (!std::filesystem::is_directory(folderPath))
			std::filesystem::create_directory(folderPath);

		std::ofstream saveFile(filePath);

		saveFile << "test";
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