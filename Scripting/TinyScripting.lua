
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
      "Include/"
   }

   sysincludedirs {
      "Include",
      "Source/clingLib/include"
   }


   filter { "system:not windows" }
            linkoptions { 
"-L../Libs -lLLVMSelectionDAG -lLLVMAArch64Disassembler -lclangRewrite -lLLVMHexagonAsmParser -lLLVMARMAsmPrinter -lLLVMXCoreAsmPrinter -lLLVMHexagonDisassembler -lLLVMDlltoolDriver -lclangToolingCore -lLLVMPowerPCInfo -lLLVMMCJIT -lclangStaticAnalyzerCore -lLLVMAsmPrinter -lLLVMLanaiDesc -lLLVMAArch64CodeGen -lLLVMipo -lclangToolingRefactor -lLLVMMSP430Info -lLLVMHexagonCodeGen -lLLVMAMDGPUAsmParser -lLLVMMIRParser -lLLVMMipsAsmPrinter -lLLVMSystemZAsmPrinter -lLLVMTransformUtils -lclang -lLLVMSystemZCodeGen -lLLVMVectorize -lLLVMXCoreCodeGen -lclangDriver -lLLVMXCoreDesc -lclangIndex -lLLVMInstCombine -lLLVMARMInfo -lclangRewriteFrontend -lLLVMAMDGPUAsmPrinter -lLTO -lLLVMDemangle -lLLVMSparcAsmPrinter -lLLVMXCoreDisassembler -lLLVMMipsInfo -lLLVMSparcDesc -lclangStaticAnalyzerFrontend -lLLVMBinaryFormat -lLLVMAsmParser -lLLVMMSP430Desc -lLLVMLanaiAsmPrinter -lclangTooling -lclingMetaProcessor -lLLVMLanaiDisassembler -lLLVMPowerPCDisassembler -lLLVMLanaiCodeGen -lLLVMAnalysis -lLLVMMipsAsmParser -lLLVMOption -lclingInterpreter -lclangDynamicASTMatchers -lLLVMCoverage -lLLVMLibDriver -lLLVMAArch64Utils -lclangBasic -lLLVMAMDGPUUtils -lLLVMAMDGPUInfo -lLLVMCodeGen -lLLVMHexagonInfo -lLLVMObjCARCOpts -lLLVMX86Info -lLLVMCore -lclangStaticAnalyzerCheckers -lclangAST -lLLVMMSP430AsmPrinter -lLLVMARMDisassembler -lLLVMX86Desc -lLLVMAMDGPUDisassembler -lLLVMARMDesc -lLLVMLinker -lLLVMObject -lLLVMLineEditor -lLLVMNVPTXInfo -lLLVMSymbolize -lLLVMPowerPCAsmPrinter -lLLVMSparcAsmParser -lLLVMX86Utils -lLLVMAArch64AsmParser -lclangFrontendTool -lLLVMMCParser -lLLVMAMDGPUCodeGen -lLLVMBitReader -lclingUtils -lLLVMAMDGPUDesc -lLLVMNVPTXCodeGen -lLLVMGlobalISel -lLLVMBPFDesc -lLLVMX86CodeGen -lLLVMBitWriter -lLLVMBPFDisassembler -lclangSerialization -lclangCodeGen -lclangASTMatchers -lLLVMSystemZAsmParser -lLLVMSystemZDisassembler -lLLVMSparcInfo -lLLVMDebugInfoMSF -lLLVMSystemZDesc -lclangAnalysis -lLLVMPowerPCAsmParser -lLLVMMipsDesc -lLLVMOrcJIT -lLLVMPowerPCDesc -lclangLex -lclangSema -lLLVMAArch64Desc -lLLVMARMCodeGen -lLLVMAArch64Info -lLLVMMipsCodeGen -lLLVMTableGen -lclangARCMigrate -lLLVMX86AsmParser -lLLVMDebugInfoDWARF -lLLVMSystemZInfo -lLLVMDebugInfoCodeView -lLLVMDebugInfoPDB -lLLVMInterpreter -lclangEdit -lLLVMHexagonDesc -lLLVMLanaiInfo -lLLVMMipsDisassembler -lLLVMScalarOpts -lclangFormat -lLLVMProfileData -lLLVMNVPTXAsmPrinter -lLLVMARMAsmParser -lLLVMRuntimeDyld -lLLVMXCoreInfo -lLLVMTarget -lLLVMX86Disassembler -lLLVMLTO -lclingJupyter -lcling -lLLVMCoroutines -lclangParse -lLLVMMC -lLLVMObjectYAML -lLLVMInstrumentation -lLLVMSparcDisassembler -lLLVMMSP430CodeGen -lclangFrontend -lLLVMBPFCodeGen -lLLVMAArch64AsmPrinter -lLLVMNVPTXDesc -lLLVMXRay -lLLVMIRReader -lLLVMLanaiAsmParser -lLLVMExecutionEngine -lLLVMBPFAsmPrinter -lLLVMPasses -lclingDemoPlugin -lLLVMMCDisassembler -lLLVMX86AsmPrinter -lLLVMBPFInfo -lLLVMPowerPCCodeGen -lLLVMSparcCodeGen -lLLVMSupport"
}

postbuildcommands { 

"cp ../Libs/libclang.dylib ../bin/Debug/libclang.dylib",
"cp ../Libs/libcling.dylib ../bin/Debug/libcling.dylib",
"cp ../Libs/libclingDemoPlugin.dylib ../bin/Debug/libclingDemoPlugin.dylib",
"cp ../Libs/libclingJupyter.dylib ../bin/Debug/libclingJupyter.dylib",
"cp ../Libs/libLTO.dylib ../bin/Debug/libLTO.dylib",
}
    
   filter "configurations:Debug"
      defines { "DEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      symbols "On"
      cppdialect "C++14"

   filter "configurations:Release"
      defines { "NDEBUG", "HAVE_DLFCN_H", "HAVE_DLOPEN" }
      optimize "On"
      cppdialect "C++14"

