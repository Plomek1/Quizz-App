project "AppGUI"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

	  -- Include Core
	  "../Core/Source",

      "../Dependencies/GLFW/lib",
      "../Dependencies/GLFW/include",
      "../Dependencies/imgui"
   }

   libdirs { "../Dependencies/GLFW/lib" }

   links
   {
      "Core",
      "glfw3",
      "opengl32",
      "ImGui"
   }

   targetdir (workspaceDir .. "/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir (workspaceDir .. "/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"