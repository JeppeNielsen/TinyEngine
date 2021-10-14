//
//  testScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 11/01/2021.
//

#include <iostream>
#include "ScriptingEngine.hpp"
#include <chrono>
#include <thread>
#include <sstream>

using namespace Tiny;


template<class T>
struct Collection {
    T inner;
};

struct Position {
    int x;
    int y;
};


int main() {
    
    ScriptingEngine engine("/Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin");
    ScriptingContext context;
    
    context.hppFiles.push_back("Scripts/Vector2.hpp");
    context.cppFiles.push_back("Scripts/TestScript.cpp");
    
    while (true) {
        
        
        //freopen("new_stdout","w",stdout);
       
        if(!engine.Compile(context)) {
            std::cout << " compilation failed:" << std::endl;
            std::cout << engine.GetCompilationErrors() << std::endl;
            return 1;
        }
        
        //freopen("/dev/tty","r",stdout);
        
        auto getResult = engine.GetFunction<int()>("GetResult");
        int result = getResult();
        std::cout << "result from script : " << result << "\n";
        
        std::chrono::nanoseconds sleepTime(100000);
        
        std::this_thread::sleep_for(sleepTime);
        
        break;
    }
        
    return 0;
}
