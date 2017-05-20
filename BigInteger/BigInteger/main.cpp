//
//  main.cpp
//  BigInteger
//
//  Created by Vadim on 21.04.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include "big_integer.h"
#include <stack>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("100000000000000000000000000000000000000000000000000000");
    cout << (a / b) << endl << c << endl;
    return 0;
}
//10000000000000000000000000
//10000000000000000000
//4294967297000000000

/*
 2   1   0
 987|654|321 << 2
 0:  tmp = 32100
 ans[i] = 100
 tmp = 032
 1: tmp = 65432
 ans[i] = 432
 tmp = 065
 2: tmp = 98765
 ans[i] = 765
 tmp = 098
 new: ans.push(098)
 => 098|765|432|100
 */
