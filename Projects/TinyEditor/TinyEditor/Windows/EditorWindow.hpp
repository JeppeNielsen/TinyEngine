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
#include "EditorScene.hpp"

namespace Editor {
    class Window;
    class EditorWindow {
    public:
        
        void CreateMain(const std::string& title, int width, int height);
        void CreateTool(const std::string& title);
        
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
        
    private:
        using WindowHandle = void*;
        
        WindowHandle window = nullptr;
        
        WindowHandle windowDelegate = nullptr;
        
        WindowHandle view = nullptr;
        
    public:
        EditorScene* editorScene = nullptr;
    };
}
