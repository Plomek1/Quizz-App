#include "MainMenu.h"

#include "MenuHandler.h"
#include <imgui.h>

namespace AppGui 
{
    void MainMenu::RenderMenu()
	{
        bool p_open;
        ImGui::Begin("Main Menu", &p_open, menuFlags);

        int sizeX, sizeY;
        ImGui::SetWindowPos(ImVec2(0, 0));
        handler.GetWindowSize(sizeX, sizeY);
        ImGui::SetWindowSize(ImVec2(sizeX, sizeY));


        if (ImGui::Button("Gameplay Menu"))
            handler.ChangeMenu(1);
        
        if (ImGui::Button("Quit"))
            handler.ExitGame();

        ImGui::End();
	}
}