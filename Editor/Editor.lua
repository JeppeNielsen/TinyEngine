require "clion"

location "Editor/Project"

include "../../Make/TinyEngineLib.lua"

project "TinyEditor"
   kind "WindowedApp" 
   language "C++"
   filter { "system:windows" }
        targetdir "bin/%{cfg.buildcfg}"
   filter { "system:not windows" }
        targetdir "bin/%{cfg.buildcfg}/TinyEditor.app/Contents/MacOS/"

   files { 
      "Editor/Code/**.cpp",
      "Editor/Code/**.hpp",
      "Editor/Code/**.mm",
   }

   includedirs {
      "Editor/Code",
      "../Tiny/**",
      "../External/minijson_writer",
      "../External/minijson_reader",
      "../External/glm",
      "../Scripting/Include",
   }

   links { "TinyEngine" }

   filter { "system:windows" }
      links { "OpenGL32" }
      
   filter { "system:not windows" }
      links { "Cocoa.framework", "CoreVideo.framework", "OpenGL.framework" }
      files { 
         "../Tiny/Platform/OSX/**.h"
      }
      linkoptions { 
         "-L${CMAKE_CURRENT_SOURCE_DIR}/../../../Scripting/Libs -lclang -lcling",
         "-L${CMAKE_CURRENT_SOURCE_DIR}/../../../Scripting/bin/Debug/ -lTinyScriptingEngine",
         "-Wl,-rpath,.",
         "-rpath @executable_path/"
      }

      postbuildcommands {
         "cp ${CMAKE_CURRENT_SOURCE_DIR}/../../../Scripting/Libs/libclang.dylib ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/%{cfg.buildcfg}/TinyEditor.app/Contents/MacOS/libclang.dylib",
         "cp ${CMAKE_CURRENT_SOURCE_DIR}/../../../Scripting/Libs/libcling.dylib ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/%{cfg.buildcfg}/TinyEditor.app/Contents/MacOS/libcling.dylib",
      }
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      cppdialect "C++17"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      cppdialect "C++17"
