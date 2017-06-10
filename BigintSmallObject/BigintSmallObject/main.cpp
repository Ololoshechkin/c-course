//
//  main.cpp
//  BigintSmallObject
//
//  Created by Vadim on 03.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include <string>
#include "big_integer.h"
#include "bigint_data.h"
using namespace std;

int main(int argc, const char * argv[]) {
    cout << sizeof(my_shared_ptr) / sizeof(uint32_t) << endl;
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("100000000000000000000000000000000000000000000000000000");
    if (a / b == c)
        cout << "ok\n";
    else
        cout << "!ok\n";
    cout << a / b << endl << c << endl;
    return 0;
}
