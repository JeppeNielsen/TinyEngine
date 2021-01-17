
workspace "TinyEngine"
   configurations { "Debug", "Release" }
   buildoptions { "-Wno-deprecated-declarations" }

project "TinyEngine"
   kind "StaticLib" 
   language "C++"
   targetdir "../bin/%{cfg.buildcfg}"
   

   files { 
      "../Tiny/**.hpp", 
      "../Tiny/**.cpp",
   }

   includedirs {
      "../Tiny/**",
      "../Tiny/Libs/"
   }

   sysincludedirs {
      "../Tiny/Libs"
   }

   filter { "system:windows" }
      links { "OpenGL32" }
      
   filter { "system:not windows" }
      links { "Cocoa.framework", "CoreVideo.framework", "OpenGL.framework" }
      files { 
         "../Tiny/Platform/OSX/**.h", 
         "../Tiny/Platform/OSX/**.mm", 
      }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      cppdialect "C++17"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      cppdialect "C++17"

