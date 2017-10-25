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
    big_integer a(2);
    big_integer b(2);
    big_integer c = a + b;
    cout << c << '\n';
    return 0;
}
