//
//  main.cpp
//  set_no_balance
//
//  Created by Vadim on 24.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include "set.h"

int main(int argc, const char * argv[]) {
    set<int> s;
    for (int i = 0; i < 20; ++i)
        s.insert(rand() % 20);
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    std::cout << "*(--end()) = " << *(--s.end());
    std::cout << '\n';
    s.erase(1);
    s.erase(3);
    s.insert(5);
    s.insert(10);
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    for (set<int>::reverse_iterator it = s.rbegin(); it != s.rend(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    return 0;
}
