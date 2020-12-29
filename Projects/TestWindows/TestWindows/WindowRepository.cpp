//
//  WindowRepository.cpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "WindowRepository.hpp"

using namespace Editor;

EditorWindow& WindowRepository::CreateWindow(const std::string& title, int width, int height) {
    EditorWindow window(title, width, height);
    
    windows.emplace_back(std::move(window));
    return windows.back();
}
