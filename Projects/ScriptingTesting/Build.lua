
location "Build"

workspace "ScriptingTesting"
   configurations { "Debug", "Release" }
   buildoptions { "-std=c++14", "-fno-rtti" }
   
project "ScriptingTesting"
   kind "ConsoleApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
      "Source/**.cpp",
      "Source/**.hpp",
   }
   
   sysincludedirs {
      "../../Scripting/Include",
      "Include",
      "../../Tiny/ECS",
      "../../Tiny/",
      "../../Tiny/Reflection",
      "../../Tiny/Serialization",
      "../../External/minijson_writer",
      "../../External/minijson_reader"
   }

   filter { "system:not windows" }
      linkoptions { 
         "-L../../../Scripting/Libs -lclang -lcling",
         "-L../../../Scripting/bin/Debug/ -lTinyScriptingEngine",
         "-Wl,-rpath,."
      }
      
   postbuildcommands { 
      "cp ../../../Scripting/Libs/libclang.dylib ../bin/Debug/libclang.dylib",
      "cp ../../../Scripting/Libs/libcling.dylib ../bin/Debug/libcling.dylib",
   }
    
   filter "configurations:Debug"
      defines { "DEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      symbols "On"
      cppdialect "C++14"

   filter "configurations:Release"
      defines { "NDEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      optimize "On"
      cppdialect "C++14"