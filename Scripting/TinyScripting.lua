
location "Generated"

workspace "TinyScripting"
   configurations { "Debug", "Release" }
   buildoptions { "-std=c++14", "-fno-rtti" }

project "TinyScripting"
   kind "ConsoleApp" 
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   

   files { 
      "Source/**.h", 
      "Source/**.cpp"
   }

   includedirs {
      "Source/cling/include/**",
   }

   sysincludedirs {
      "Source/cling/libs",
      "Source/cling/include",
      "Source/clingLib/include",
   }

   filter { "system:windows" }
      
   filter { "system:not windows" }
      libdirs { "Source/cling/libs"}
      buildoptions {"-F ../Source/cling/libs"}
      linkoptions {"-F ../Source/cling/libs"}
      links { 
"LLVMAArch64AsmParser",
"LLVMAArch64AsmPrinter",
"LLVMAArch64CodeGen",
"LLVMAArch64Desc",
"LLVMAArch64Disassembler",
"LLVMAArch64Info",
"LLVMAArch64Utils",
"LLVMAMDGPUAsmParser",
"LLVMAMDGPUAsmPrinter",
"LLVMAMDGPUCodeGen",
"LLVMAMDGPUDesc",
"LLVMAMDGPUDisassembler",
"LLVMAMDGPUInfo",
"LLVMAMDGPUUtils",
"LLVMARMAsmParser",
"LLVMARMAsmPrinter",
"LLVMARMCodeGen",
"LLVMARMDesc",
"LLVMARMDisassembler",
"LLVMARMInfo",
"LLVMAnalysis",
"LLVMAsmParser",
"LLVMAsmPrinter",
"LLVMBPFAsmPrinter",
"LLVMBPFCodeGen",
"LLVMBPFDesc",
"LLVMBPFDisassembler",
"LLVMBPFInfo",
"LLVMBinaryFormat",
"LLVMBitReader",
"LLVMBitWriter",
"LLVMCodeGen",
"LLVMCore",
"LLVMCoroutines",
"LLVMCoverage",
"LLVMDebugInfoCodeView",
"LLVMDebugInfoDWARF",
"LLVMDebugInfoMSF",
"LLVMDebugInfoPDB",
"LLVMDemangle",
"LLVMDlltoolDriver",
"LLVMExecutionEngine",
"LLVMGlobalISel",
"LLVMHexagonAsmParser",
"LLVMHexagonCodeGen",
"LLVMHexagonDesc",
"LLVMHexagonDisassembler",
"LLVMHexagonInfo",
"LLVMIRReader",
"LLVMInstCombine",
"LLVMInstrumentation",
"LLVMInterpreter",
"LLVMLTO",
"LLVMLanaiAsmParser",
"LLVMLanaiAsmPrinter",
"LLVMLanaiCodeGen",
"LLVMLanaiDesc",
"LLVMLanaiDisassembler",
"LLVMLanaiInfo",
"LLVMLibDriver",
"LLVMLineEditor",
"LLVMLinker",
"LLVMMC",
"LLVMMCDisassembler",
"LLVMMCJIT",
"LLVMMCParser",
"LLVMMIRParser",
"LLVMMSP430AsmPrinter",
"LLVMMSP430CodeGen",
"LLVMMSP430Desc",
"LLVMMSP430Info",
"LLVMMipsAsmParser",
"LLVMMipsAsmPrinter",
"LLVMMipsCodeGen",
"LLVMMipsDesc",
"LLVMMipsDisassembler",
"LLVMMipsInfo",
"LLVMNVPTXAsmPrinter",
"LLVMNVPTXCodeGen",
"LLVMNVPTXDesc",
"LLVMNVPTXInfo",
"LLVMObjCARCOpts",
"LLVMObject",
"LLVMObjectYAML",
"LLVMOption",
"LLVMOrcJIT",
"LLVMPasses",
"LLVMPowerPCAsmParser",
"LLVMPowerPCAsmPrinter",
"LLVMPowerPCCodeGen",
"LLVMPowerPCDesc",
"LLVMPowerPCDisassembler",
"LLVMPowerPCInfo",
"LLVMProfileData",
"LLVMRuntimeDyld",
"LLVMScalarOpts",
"LLVMSelectionDAG",
"LLVMSparcAsmParser",
"LLVMSparcAsmPrinter",
"LLVMSparcCodeGen",
"LLVMSparcDesc",
"LLVMSparcDisassembler",
"LLVMSparcInfo",
--"LLVMSupport",
"LLVMSymbolize",
"LLVMSystemZAsmParser",
"LLVMSystemZAsmPrinter",
"LLVMSystemZCodeGen",
"LLVMSystemZDesc",
"LLVMSystemZDisassembler",
"LLVMSystemZInfo",
"LLVMTableGen",
"LLVMTarget",
"LLVMTransformUtils",
"LLVMVectorize",
"LLVMX86AsmParser",
"LLVMX86AsmPrinter",
"LLVMX86CodeGen",
"LLVMX86Desc",
"LLVMX86Disassembler",
"LLVMX86Info",
"LLVMX86Utils",
"LLVMXCoreAsmPrinter",
"LLVMXCoreCodeGen",
"LLVMXCoreDesc",
"LLVMXCoreDisassembler",
"LLVMXCoreInfo",
"LLVMXRay",
"LLVMipo",
"clangARCMigrate",
"clangAST",
"clangASTMatchers",
"clangAnalysis",
"clangBasic",
"clangCodeGen",
"clangDriver",
"clangDynamicASTMatchers",
"clangEdit",
"clangFormat",
"clangFrontend",
"clangFrontendTool",
"clangIndex",
"clangLex",
"clangParse",
"clangRewrite",
"clangRewriteFrontend",
"clangSema",
"clangSerialization",
"clangStaticAnalyzerCheckers",
"clangStaticAnalyzerCore",
"clangStaticAnalyzerFrontend",
"clangTooling",
"clangToolingCore",
"clangToolingRefactor",
"clingInterpreter",
"clingMetaProcessor",
"clingUserInterface",
"clingUtils",
"LTO",
"clang",
"cling",
"clingDemoPlugin",
"clingJupyter",

}
      
   filter "configurations:Debug"
      defines { "DEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      symbols "On"
      cppdialect "C++14"

   filter "configurations:Release"
      defines { "NDEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      optimize "On"
      cppdialect "C++14"
