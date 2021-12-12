//
//  main.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "Engine.hpp"
#include "MainState.hpp"

using namespace Tiny;

int main() {
    Engine e;
    e.Start<TinyEditor::MainState>();
    
    return EXIT_SUCCESS;
}
