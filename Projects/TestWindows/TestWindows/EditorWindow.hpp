//
//  EditorWindow.hpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <string>

namespace Editor {
    class EditorWindow {
    public:
        EditorWindow(const std::string& title, int width, int height);
        ~EditorWindow();
    private:
        using WindowHandle = void*;
        
        WindowHandle window;
    };
}
