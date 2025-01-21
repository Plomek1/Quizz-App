#include "GameplayMenu.h"

#include "MenuHandler.h"
#include "SaveManager/SaveManager.h"

#include <imgui.h>

#include <iostream>

namespace AppGui
{
    void GameplayMenu::OpenMenu() { Core::LoadQuizzes(quizzes); }

    void GameplayMenu::CloseMenu() 
    { 
        if (playingQuiz) ExitQuiz();
        quizzes.clear();
    }

    void GameplayMenu::RenderMenu()
    {
        bool p_open;
        ImGui::Begin("Gameplay Menu", &p_open, menuFlags);

        int sizeX, sizeY;
        ImGui::SetWindowPos(ImVec2(0, 0));
        handler.GetWindowSize(sizeX, sizeY);
        ImGui::SetWindowSize(ImVec2(sizeX, sizeY));


        playingQuiz ? RenderQuizGameplay() : RenderQuizSelection();

        ImGui::End();
    }

    void GameplayMenu::PlayQuiz(Core::Quiz& quiz)
    {
        std::cout << "Playing: " << quiz.title << std::endl;
        playingQuiz = true;
        activeQuiz = { &quiz, 0, 0};
    }

    void GameplayMenu::ExitQuiz()
    {
        playingQuiz = false;
        activeQuiz = {};
    }


    void GameplayMenu::RenderQuizSelection()
    {
        for (Core::Quiz& quiz : quizzes)
        {
            if (ImGui::Button(quiz.title.c_str()))
                PlayQuiz(quiz);
        }

        if (ImGui::Button("Main Menu"))
            handler.ChangeMenu(0);
    }

    void GameplayMenu::RenderQuizGameplay()
    {
        
        unsigned int questionsCount = activeQuiz.quiz->questions.size();
        if (activeQuiz.currentQuestion == questionsCount)
        {
            std::string prompt = "Quiz over!\nYour score: " + std::to_string(activeQuiz.score) + '/' + std::to_string(questionsCount);
            ImGui::Text(prompt.c_str());

            if (ImGui::Button("Select another quiz"))
                ExitQuiz();
            if (ImGui::Button("Return to main menu"))
                handler.ChangeMenu(0);
            return;
        }

        std::string title = activeQuiz.quiz->title + "     " + std::to_string(activeQuiz.score) + '/' + std::to_string(questionsCount);
        ImGui::Text(title.c_str());
        
        Core::Question currentQuestion = activeQuiz.quiz->questions[activeQuiz.currentQuestion];

        ImGui::Spacing();
        ImGui::Text(currentQuestion.title.c_str());

        for (int i = 0; i < currentQuestion.answers.size(); i++)
        {
            std::string answer = std::to_string(i + 1) + ". " + currentQuestion.answers[i];
            if (ImGui::Button(answer.c_str()))
            {
                if (currentQuestion.correctAnswerIndex == i) activeQuiz.score++;
                activeQuiz.currentQuestion++;
            }
        }
    }
}