
location "Build"

workspace "TinyScriptingEngine"
   configurations { "Debug", "Release" }
   buildoptions { "-std=c++14", "-fno-rtti" }
   
project "TinyScriptingEngine"
   kind "ConsoleApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
      "Source/**.h", 
      "Source/**.cpp",
      "Include/**.hpp", 
      "TestCode/main.cpp"
   }
   
   includedirs {
      "Include"
   }

   sysincludedirs {
      "Libs/include",
   }


   filter { "system:not windows" }
            linkoptions { 
"-L../Libs/ -lcling -lclang"
}

postbuildcommands { 

"cp ../Libs/libclang.dylib ../bin/Debug/libclang.dylib",
"cp ../Libs/libcling.dylib ../bin/Debug/libcling.dylib",
}
    
   filter "configurations:Debug"
      defines { "DEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN", "LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING" }
      symbols "On"
      cppdialect "C++14"

   filter "configurations:Release"
      defines { "NDEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN", "LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING" }
      optimize "On"
      cppdialect "C++14"

