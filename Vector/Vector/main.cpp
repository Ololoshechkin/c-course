//
//  main.cpp
//  Vector
//
//  Created by Vadim on 22.04.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include "vector.hpp"

int main(int argc, const char * argv[]) {
    vector<int> x;
    for (int it = 0; it < 100500; ++it) {
        for (int i = 0; i < 10; ++i)
            x.push_back(10 * i);
        for (int i = 0; i < 5; ++i)
            x.pop_back();
    }
    x.clear();
    return 0;
}
