//
//  main.cpp
//  sanitizer_and_other_tools
//
//  Created by Vadim on 06.05.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    // ctrl+shift+b
    int a[10];
    cout << a[11];
    int*b = new int(2);
    delete b;
    *b = 10;
    return 0;
}
