//
//  main.cpp
//  constructor_new_delete_lection
//
//  Created by Vadim on 25.03.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

string f(string s)
{
    return s + "!";
}

string f(char const*) = delete;

int main(int argc, const char * argv[]) {
    
    int *p = new int(5);
    int *t = new(p) int(100);
    cout << *t << ' ' << *p << endl;
    string s("hello, world");
    cout << f(s) << endl;
    //cout << f("none") << endl; // exception!
    
    return 0;
}
