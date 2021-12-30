require "clion"

location "Build"

workspace "DragAndDock"
   configurations { "Debug", "Release" }

project "DragAndDock"
   kind "WindowedApp" 
   language "C++"

   filter { "system:windows" }
        targetdir "bin/%{cfg.buildcfg}"

   filter { "system:not windows" }
        targetdir "bin/%{cfg.buildcfg}/DragAndDock.app/Contents/MacOS/"
   

   files { 
      "../../Tiny/**.hpp", 
      "../../Tiny/**.cpp",
      "Source/**.cpp",
   }

   includedirs {
      "../../Tiny/**",
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/",
   }

   sysincludedirs {
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/",
   }

   filter { "system:windows" }
      links { "OpenGL32" }
      
   filter { "system:not windows" }
      links { "Cocoa.framework", "CoreVideo.framework", "OpenGL.framework" }
      files { 
         "../../Tiny/Platform/OSX/**.h", 
         "../../Tiny/Platform/OSX/**.mm", 
      }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      cppdialect "C++17"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      cppdialect "C++17"
