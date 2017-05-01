//
//  main.cpp
//  BigInteger
//
//  Created by Vadim on 21.04.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include "big_integer.h"
using namespace std;

int main(int argc, const char * argv[]) {
    big_integer a = big_integer("1312313133133131331") - big_integer("24151213214123123125123231293812938193819310293012858329041023804");
    big_integer b = big_integer("99999999999999911111111111111999991");
    big_integer c = big_integer("1231313123013019320912039120388231819231") * 10;
    big_integer ans = -(a ^ b | c);
    cout << a << "\n" << b << "\n" << c << "\n\n " << ans << endl;
    return 0;
}
//10000000000000000000000000
//10000000000000000000
//4294967297000000000
