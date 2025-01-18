project "ImGui"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "*.h", "*.cpp" }

   includedirs 
   {
        "../GLFW/lib",
        "../GLFW/include",
    }

   libdirs { "../GLFW/lib" }

   links{ "glfw3" }

   targetdir (workspaceDir .. "/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir (workspaceDir .. "/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   
   filter "system:windows"
       systemversion "latest"
       defines { }

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