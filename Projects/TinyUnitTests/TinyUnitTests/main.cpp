//
//  main.cpp
//  TinyUnitTests
//
//  Created by Jeppe Nielsen on 06/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include <iostream>
#include "ECSTests.hpp"
#include "LogicTests.hpp"

int main() {
    
    std::cout << "ECS tests: \n";
    ECSTests ecsTests;
    ecsTests.Run();
    
    std::cout << "\nLogic tests: \n";
    LogicTests logicTests;
    logicTests.Run();
    
    
    return 0;
}
