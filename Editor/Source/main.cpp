//
//  main.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "Engine.hpp"
#include "MainWindow.hpp"

using namespace Tiny;

int main() {
    Engine e;
    e.Start<TinyEditor::MainWindow>();
    
    return EXIT_SUCCESS;
}
