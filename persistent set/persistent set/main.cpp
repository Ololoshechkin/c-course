//
//  main.cpp
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include "shared_ptr.h"
#include "linked_ptr.h"
#include "persistent_set.h"

int main(int argc, const char * argv[]) {
    auto p = shared_ptr<std::string>::of("kek");
    std::cout << *p << std::endl;
    persistent_set<int> s;
    persistent_set<int, linked_ptr> s2;
    return 0;
}
