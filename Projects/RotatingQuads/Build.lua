
location "Build"

include "../../Make/TinyEngineLib.lua"

project "RotatingQuads"
   kind "WindowedApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
      "Source/*.cpp"
   }

   includedirs {
      "../../Tiny/**"
   }

   sysincludedirs {
      "../../Tiny/Libs"
   }

   links { "TinyEngine" }

   filter { "system:windows" }
      links { "OpenGL32" }
      
   filter { "system:not windows" }
      links { "Cocoa.framework", "CoreVideo.framework", "OpenGL.framework" }
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      cppdialect "C++17"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      cppdialect "C++17"
