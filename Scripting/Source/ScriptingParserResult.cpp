//
//  ScriptingParserResult.cpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 19/10/2021.
//

#include "ScriptingParserResult.hpp"

using namespace Tiny;

ScriptingParserResult::Component* ScriptingParserResult::FindComponent(const std::string &name) {
    for(auto& c : components) {
        if (c.name == name) return &c;
    }
    return nullptr;
}
