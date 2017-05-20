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
#include <string>
using namespace std;

string rand_string(size_t sz) {
    string s = "";
    for (size_t i = 0; i < sz; ++i)
        s.push_back('0' + (rand() % 10));
    return s;
}

int main(int argc, const char * argv[]) {
    /*srand(time(NULL));
    int it = 0;
    while (1) {
        cout << it << endl;
        ++it;
        big_integer a(rand_string(200));
        big_integer b(rand_string(100));
        b = -b;
        big_integer c = a * b;
        if (c / a != b) {
            cout << a << endl << endl << b << endl << endl << "ab/a != b\n";
            break;
        }
        if (c / b != a) {
            cout << a << endl << endl << b << endl << endl << "ab/b != a\n";
            break;
        }
    }*/
    big_integer a("11352558046984322075629575508294687131682311458447485430196956763615108401159888387391161770306537524342375010327449380999844334878549135888908965878949522029166446924361861116427104770795741930092759");
    big_integer b("-3687766281184794409817215087303242164862572855595808584347971227283712217115359241561998727672208298");
    cout << a << endl << endl << b << endl << endl;
    cout << "a * b = " << (a * b) << endl << endl;
    cout << (a * b) / a << endl;
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
