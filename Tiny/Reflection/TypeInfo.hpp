//
//  TypeInfo.hpp
//  ECS
//
//  Created by Jeppe Nielsen on 29/11/2018.
//  Copyright © 2018 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <string>
#include <vector>
#include "FieldInfo.hpp"
#include "minijson_reader.hpp"
#include "minijson_writer.hpp"

namespace Tiny {
    class TypeInfo {
    public:
        using FieldCollection = std::vector<FieldInfo>;
    
        TypeInfo(const std::string& name);
        TypeInfo(TypeInfo&&) = default;
        void Serialize(minijson::object_writer& writer);
        void Deserialize(minijson::istream_context& context);
        const std::string& Name() const;
        bool TryFindField(const std::string& name, FieldInfo& info);
        
        template<typename T>
        void AddField(const std::string& name, T& field) {
            fields.emplace_back(FieldInfo(name, field));
        }
        
        const FieldCollection& Fields() const;
    public:
        std::string name;
        
        FieldCollection fields;
    };

}
