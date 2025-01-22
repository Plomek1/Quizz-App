#include "GameplayMenu.h"

#include "MenuHandler.h"
#include "SaveManager/SaveManager.h"

#include <imgui.h>

namespace AppGui
{
    void GameplayMenu::OpenMenu() { Core::LoadQuizzes(quizzes); }

    void GameplayMenu::CloseMenu() 
    { 
        if (menuState == LIST) ExitQuiz();

        if (quizDeleted)
        {
            Core::SaveQuizzes(quizzes);
            quizDeleted = true;
        }
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

        switch (menuState)
        {
        case LIST:
            RenderQuizList();
            break;
        case SELECTED:
            RenderSelectedQuiz();
            break;
        case PLAYING:
            RenderPlayedQuiz();
            break;
        }
        
        ImGui::End();
    }

    void GameplayMenu::SelectQuiz(Core::Quiz& quiz)
    {
        menuState = SELECTED;
        activeQuiz = { &quiz, 0, 0};
    }

    void GameplayMenu::StartQuiz()
    {
        menuState = PLAYING;
    }

    void GameplayMenu::ExitQuiz()
    {
        menuState = LIST;
        activeQuiz = {};
    }

    void GameplayMenu::DeleteQuiz(Core::Quiz& quiz)
    {
        for (int i = 0; i < quizzes.size(); i++)
        {
            if (&quizzes[i] == &quiz)
            {
                quizzes.erase(quizzes.begin() + i);
                break;
            }
        }

        quizDeleted = true;
    }

    void GameplayMenu::RenderQuizList()
    {
        for (Core::Quiz& quiz : quizzes)
        {
            if (ImGui::Button(quiz.title.c_str()))
                SelectQuiz(quiz);
        }

        if (ImGui::Button("Main Menu"))
            handler.ChangeMenu(0);
    }

    void GameplayMenu::RenderSelectedQuiz()
    {
        std::string title = activeQuiz.quiz->title;
        ImGui::Text(title.c_str());
        if (ImGui::Button("Play"))
            StartQuiz();
        
        if (ImGui::Button("Delete"))
        {
            DeleteQuiz(*activeQuiz.quiz);
            ExitQuiz();
        }
        
        if (ImGui::Button("Go back"))
            ExitQuiz();
    }

    void GameplayMenu::RenderPlayedQuiz()
    {
        unsigned int questionsCount = activeQuiz.quiz->questions.size();
        if (activeQuiz.currentQuestion == questionsCount)
        {
            std::string prompt = "Quiz over!\nYour score: " + std::to_string(activeQuiz.score) + '/' + std::to_string(questionsCount);
            ImGui::Text(prompt.c_str());

            if (ImGui::Button("Retry"))
            {
                SelectQuiz(*activeQuiz.quiz);
                StartQuiz();
            }
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