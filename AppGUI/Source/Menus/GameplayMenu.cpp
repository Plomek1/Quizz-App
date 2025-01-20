#include "GameplayMenu.h"

#include "MenuHandler.h"
#include "SaveManager/SaveManager.h"

#include <imgui.h>

#include <iostream>

namespace AppGui
{
    void GameplayMenu::OpenMenu() { Core::LoadQuizzes(quizzes); }
    void GameplayMenu::CloseMenu() { quizzes.clear(); }

    void GameplayMenu::RenderMenu()
    {
        bool p_open;
        ImGui::Begin("Gameplay Menu", &p_open, menuFlags);

        int sizeX, sizeY;
        ImGui::SetWindowPos(ImVec2(0, 0));
        handler.GetWindowSize(sizeX, sizeY);
        ImGui::SetWindowSize(ImVec2(sizeX, sizeY));


        for (Core::Quiz quiz : quizzes)
        {
            if(ImGui::Button(quiz.title.c_str()))
                PlayQuiz(quiz);
        }

        if (ImGui::Button("Main Menu"))
            handler.ChangeMenu(0);

        ImGui::End();
    }
    void GameplayMenu::PlayQuiz(Core::Quiz& quiz)
    {
        std::cout << "Playing: " << quiz.title << std::endl;
    }
}