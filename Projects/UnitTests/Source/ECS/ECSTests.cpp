//
//  Tests.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 01/11/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//
#include <iostream>
#include "ECSTests.hpp"
#include "TestComponentContainer.hpp"
#include "TestGameObjectDatabase.hpp"
#include "TestTaskRunner.hpp"
#include "SceneTests.hpp"

void ECSTests::Run() {

    {
        std::cout << "\nComponentContainer : " << std::endl;
        TestComponentContainer test;
        test.Run();
    }
    {
        std::cout << "\nGameObjectDatabase : " << std::endl;
        TestGameObjectDatabase test;
        test.Run();
    }
    
    {
        std::cout << "\nTaskRunner : " << std::endl;
        TestTaskRunner test;
        test.Run();
    }
    
    {
        std::cout << "\nScene Tests : " << std::endl;
        SceneTests test;
        test.Run();
    }
    
    {
        std::cout << "\nDependencies Tests : " << std::endl;
        SceneTests test;
        test.Run();
    }


}
