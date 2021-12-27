//
//  EditorWindow.hpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <string>
#include "Math.hpp"

namespace TinyEditor {
    class Window;
    class EditorWindow {
    public:

        using WindowHandle = void*;

        void CreateMain(const std::string& title, int width, int height);
        void CreateTool(WindowHandle mainWindow, const std::string& title);
        
        void Close();
        
        bool IsCreated();
        void SetFrame(ivec2 position, ivec2 size);
        
        bool needsUpdate = false;
        ivec2 position;
        ivec2 size;
        bool isDead = false;
        vec3 color;
        
        void Update();
        void Render(ivec2 viewport);

        WindowHandle GetHandle();
        
    private:
        WindowHandle window = nullptr;
        WindowHandle windowDelegate = nullptr;
        WindowHandle view = nullptr;
    };
}
