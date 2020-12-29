//
//  WindowRepository.hpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <vector>
#include <memory>


#include "EditorWindow.hpp"

namespace Editor {
    class WindowRepository {
    public:
        
        EditorWindow& CreateWindow();
        
    private:
        using Windows = std::vector<std::shared_ptr<EditorWindow>>;
        
        Windows windows;
    };
}
