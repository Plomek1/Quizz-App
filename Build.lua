-- premake5.lua
workspaceDir = os.getcwd()

workspace "Quizz App"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "Core/Build-Core.lua"
include "AppTerminal/Build-AppTerminal.lua"
include "AppGUI/Build-AppGUI.lua"

group "Libs"
   include "Dependencies/nlohmann/Build-NlohmannJson.lua"
   include "Dependencies/imgui/Build-imgui.lua"
group ""