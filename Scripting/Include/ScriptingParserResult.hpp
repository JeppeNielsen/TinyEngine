//
//  ScriptingParserResult.hpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 19/10/2021.
//

#pragma once
#include <string>
#include <vector>

namespace Tiny {
    struct ScriptingParserResult {
    
        struct System {
            std::string name;
            std::vector<std::string> components;
        };
        
        struct Component {
            struct Field {
                std::string name;
                std::string type;
            };
        
            std::string name;
            using Fields = std::vector<Field>;
            Fields fields;
        };
        
        using Systems = std::vector<System>;
        using Components = std::vector<Component>;
    
        bool succes = false;
        Systems systems;
        Components components;
        
        Component* FindComponent(const std::string& name);
    
    };
}
