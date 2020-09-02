//
//  Test.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 22/09/2018.
//  Copyright © 2018 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <functional>
#include <string>

namespace Tiny {
    class TestBase {
    protected:
        void RunTest(const std::string& testName, const std::function<bool()>& testCode) const;
    public:
        virtual ~TestBase();
        virtual void Run() = 0;
    };
}
