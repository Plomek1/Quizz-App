#pragma once

#include <string>

namespace AppTerminal::MenuHandling
{
	const std::string DASHES_PROMPT = "-----";

	const std::string MAIN_MENU_PROMPT = "-----Quiz Game-----";
	const std::string GAMEPLAY_MENU_PROMPT = "-----Gameplay Menu-----";
	const std::string CREATOR_MENU_PROMPT = "-----Creator Menu-----";

	const std::string PLAY_PROMPT = "Press P to play";
	const std::string DELETE_PROMPT = "Press D to delete";
	const std::string RETRY_PROMPT = "Press R to try again";
	const std::string SELECT_ANOTHER_QUIZ_PROMPT = "Press S to select another quiz";
	const std::string CREATE_QUIZ_PROMPT = "Press C to create quiz";
	const std::string GOTO_MAIN_MENU_PROMPT = "Press M to go to main menu";
	const std::string GO_BACK_PROMPT = "Press B to go back";
	const std::string EXIT_PROMPT = "Press E to exit";

	const std::string PRESS_PROMPT = "Press ";
	const std::string TO_SELECT_PROMPT  = " to select ";

	const std::string QUIZ_OVER_PROMPT = "Quiz is over!";
	const std::string YOUR_SCORE_PROMPT = "Your score: ";
	
	const std::string GOODBYE_PROMPT = "See you next time!";

	const std::string INPUT_INVALID_PROMPT = "Invalid input, please try again";
	const std::string DATA_CORRUPTED_PROMPT = "Save data is corrupted!";
	const std::string NO_QUIZZES_PROMPT = "No quizzes available, please create a quiz first!";

	const char PLAY_OPTION = 'p';
	const char DELETE_OPTION = 'd';
	const char RETRY_OPTION = 'r';
	const char ANOTHER_QUIZ_OPTION = 's';
	const char CREATE_QUIZ_OPTION = 'c';
	const char MAIN_MENU_OPTION = 'm';
	const char GO_BACK_OPTION = 'b';
	const char EXIT_OPTION = 'e';

}