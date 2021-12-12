
location "Build"

include "../../Make/TinyEngineLib.lua"

project "TinyEditor"
   kind "WindowedApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
      "Source/**.cpp",
      "Source/**.hpp",
      "Source/**.mm",
   }

   includedirs {
      "../Tiny/**"
   }

   sysincludedirs {
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
         "-L../../Scripting/Libs -lclang -lcling",
         "-L../../Scripting/bin/Debug/ -lTinyScriptingEngine",
         "-Wl,-rpath,.",
         "-rpath @executable_path/"
      }

      postbuildcommands { 
         "cp ../../Scripting/Libs/libclang.dylib ../bin/Debug/TinyEditor.app/Contents/MacOS/libclang.dylib",
         "cp ../../Scripting/Libs/libcling.dylib ../bin/Debug/TinyEditor.app/Contents/MacOS/libcling.dylib",
      }
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      cppdialect "C++17"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      cppdialect "C++17"





--[[
project "TinyEditor"
   kind "WindowedApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
      "Source/**.cpp",
      "Source/**.hpp",
   }
   
   sysincludedirs {
      "../Scripting/Include",
      "../Tiny/ECS",
      "../Tiny/",
      "../Tiny/Reflection",
      "../Tiny/Serialization",
      "../External/minijson_writer",
      "../External/minijson_reader"
   }

   filter { "system:not windows" }
      linkoptions { 
         "-L../../Scripting/Libs -lclang -lcling",
         "-L../../Scripting/bin/Debug/ -lTinyScriptingEngine",
         "-Wl,-rpath,."
      }
      
   postbuildcommands { 
      "cp ../../Scripting/Libs/libclang.dylib ../bin/Debug/libclang.dylib",
      "cp ../../Scripting/Libs/libcling.dylib ../bin/Debug/libcling.dylib",
   }

   filter "configurations:Debug"
      defines { "DEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      symbols "On"
      cppdialect "C++17"
      debugdir "Build"  

   filter "configurations:Release"
      defines { "NDEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      optimize "On"
      cppdialect "C++17"

   --]]