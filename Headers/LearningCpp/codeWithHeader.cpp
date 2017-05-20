//
//  codeWithHeader.cpp
//  LearningCpp
//
//  Created by Vadim on 13.03.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include "codeWithHeader.hpp"

myClass::myClass(int value)
{
    this->value = value;
}

int myClass::getSeventeen()
{
    return 17;
}

int myClass::getValue()
{
    return value;
}

template<typename... T>
void myClass::run(const T&... args)
{
    
}
