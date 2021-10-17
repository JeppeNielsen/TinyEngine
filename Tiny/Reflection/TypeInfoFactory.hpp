//
//  FieldInfoFactory.hpp
//  TinyEngine
//
//  Created by Jeppe Nielsen on 15/10/2021.
//

#pragma once
#include "TypeInfo.hpp"

namespace Tiny {

struct TypeInfoFactory {
    template<typename T>
    static TypeInfo Create(const T& object) {
        return TypeInfo("Empty");
    }
};

}
