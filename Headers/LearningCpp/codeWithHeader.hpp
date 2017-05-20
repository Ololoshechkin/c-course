//
//  codeWithHeader.hpp
//  LearningCpp
//
//  Created by Vadim on 13.03.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef codeWithHeader_hpp
#define codeWithHeader_hpp

#include <iostream>

class myClass
{
private:
    int value;
public:
    myClass(int value);
    static int getSeventeen();
    int getValue();
    template<typename... T>
    void run(const T&... args);
};

#endif /* codeWithHeader_hpp */
