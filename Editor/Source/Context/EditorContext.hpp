//
//  EditorContext.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 12/12/2021.
//

#pragma once
#include <filesystem>

namespace TinyEditor {

struct EditorContext {
    std::filesystem::path ProjectRoot;
};

}
