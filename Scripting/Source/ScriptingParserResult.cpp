//
//  ScriptingParserResult.cpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 19/10/2021.
//

#include "ScriptingParserResult.hpp"
#include <ostream>

using namespace Tiny;

ScriptingParserResult::Component* ScriptingParserResult::FindComponent(const std::string &name) {
    for(auto& c : components) {
        if (c.name == name) return &c;
    }
    return nullptr;
}

void ScriptingParserResult::ToStream(std::ostream &stream) {
    stream << "Components:\n";
    for(auto g : components) {
        stream << g.name << "\n";
        
        for(auto field : g.fields) {
            stream << " -> " << field.type << " : " <<  field.name << "\n";
        }
    }
    
    stream << "Systems:\n";
    for (auto s : systems) {
        stream << s.name << "\n";
    }
    
}
