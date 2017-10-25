//
//  main.cpp
//  bind
//
//  Created by Vadim on 21/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include <string>
#include "bind.h"

int f(int a, int b, int c) {
    std::cout << a << b << c << std::endl;
    return a + b + c;
}

int main() {
    bind(&f, 1, 2, 3)();
    bind(&f, _1, _3, _2)(4, 6, 5);
    bind(&f, _1, bind(&f, _1, _1, _1), _2)(7, 8);
    return 0;
}
