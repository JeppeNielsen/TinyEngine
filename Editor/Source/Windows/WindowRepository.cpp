//
//  WindowRepository.cpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "WindowRepository.hpp"

using namespace TinyEditor;

EditorWindow& WindowRepository::CreateWindow() {
    auto ptr = std::make_shared<EditorWindow>();
    windows.push_back(ptr);
    return *ptr.get();
}
