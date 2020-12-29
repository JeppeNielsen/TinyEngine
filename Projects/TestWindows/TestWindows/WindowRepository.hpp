//
//  WindowRepository.hpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <deque>
#include "EditorWindow.hpp"

namespace Editor {
    class WindowRepository {
    public:
        
        EditorWindow& CreateWindow(const std::string& title, int width, int height);
        
    private:
        
        using Windows = std::deque<EditorWindow>;
        
        Windows windows;
    };
}
