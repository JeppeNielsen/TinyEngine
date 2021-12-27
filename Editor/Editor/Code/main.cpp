//
//  main.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "Engine.hpp"
#include "Editor/Editor.hpp"

using namespace Tiny;

int main() {
    Engine e;
    e.Start<TinyEditor::Editor>();
    
    return EXIT_SUCCESS;
}
