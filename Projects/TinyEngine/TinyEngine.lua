
location "Build"

workspace "TinyEngine"
   configurations { "Debug", "Release" }

project "TinyEngine"
   kind "WindowedApp" 
   language "C++"
   targetdir "../bin/%{cfg.buildcfg}"
   

   files { 
      "../../Tiny/**.hpp", 
      "../../Tiny/**.cpp",
      "Source/**.cpp",
      "Source/Info.plist",
   }

   includedirs {
      "../../Tiny/**",
   }

   sysincludedirs {
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/" 
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
