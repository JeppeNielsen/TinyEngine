require "clion"

location "Build"

workspace "ECS"
   configurations { "Debug", "Release" }

project "ECS"
   kind "ConsoleApp" 
   language "C++"

   filter { "system:windows" }
        targetdir "bin/%{cfg.buildcfg}"

   filter { "system:not windows" }
        targetdir "bin/%{cfg.buildcfg}"
   

   files { 
      "Source/**.cpp",
      "Source/**.hpp",
      "../../External/googletest/googletest/src/gtest-all.cc"
   }

   includedirs {
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/",
      "../../External/taskflow/taskflow",
      "../../External/googletest/googletest/include",
      "../../External/googletest/googletest"
   }

   sysincludedirs {
      "../../External/glm/",
      "../../External/minijson_reader/",
      "../../External/minijson_writer/",
      "../../External/taskflow/taskflow",
      "../../External/googletest/googletest/include",
      "../../External/googletest/googletest"
   }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      cppdialect "C++17"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      cppdialect "C++17"
