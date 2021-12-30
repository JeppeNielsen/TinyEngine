require "clion"

location "Build"

include "../../Make/TinyEngineLib.lua"

project "UnitTests"
   kind "ConsoleApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
      "Source/**.cpp",
      "Source/**.hpp",
   }

   includedirs {
      "../../Tiny/**",
      "Source/**",
      "../../External/minijson_writer",
      "../../External/minijson_reader",
      "../../External/glm"
   }

   sysincludedirs {
      "../../External/minijson_writer",
      "../../External/minijson_reader",
      "../../External/glm"
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
