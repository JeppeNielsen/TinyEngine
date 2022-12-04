require "clion"

location "Build"

workspace "EcsExperiments"
   configurations { "Debug", "Release" }

project "EcsExperiments"
   kind "WindowedApp" 
   language "C++"

   filter { "system:windows" }
        targetdir "bin/%{cfg.buildcfg}"

   filter { "system:not windows" }
        targetdir "bin/%{cfg.buildcfg}/EcsExperiments.app/Contents/MacOS/"
   

   files { 
      "Source/**.cpp"
   }

   includedirs {
      "../../Tiny/**",
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/",
      "../../External/taskflow/taskflow"
   }

   sysincludedirs {
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/",
      "../../External/taskflow/taskflow"
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
