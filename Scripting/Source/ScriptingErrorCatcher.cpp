//
//  ScriptingErrorCatcher.cpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 14/10/2021.
//

#include "ScriptingErrorCatcher.hpp"


using namespace Tiny;

ScriptingErrorCatcher::ScriptingErrorCatcher(std::stringstream& outputStream) {
   oldBuffer = std::cerr.rdbuf();
   std::cerr.rdbuf (outputStream.rdbuf());
}
   
ScriptingErrorCatcher::~ScriptingErrorCatcher() {
   std::cerr.rdbuf (oldBuffer);
}
