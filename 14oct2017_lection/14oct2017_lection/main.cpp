//
//  main.cpp
//  14oct2017_lection
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include <experimental/optional>
#include <vector>
using namespace std;
using namespace std::placeholders;
using namespace std::experimental;

struct str {
    explicit operator string() {
        return "abacabadabacabaeabacabadabacaba";
    }
};

template <typename T>
struct my_optional {
    bool valid;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
    ///...///
};

int main(int argc, const char * argv[]) {
    auto sum = [](int x, int y) { return  x + y; };
    auto inc = bind(sum, 1, _1);
    cout << inc(5) << endl;///6
    optional<int> s = 100;// = 5;
    cout << (bool)s << endl;
    str st;
    cout << (string)st << endl;
    unique_ptr<int> a = make_unique<int>(1);
    unique_ptr<int> b = make_unique<int>(2);
    vector<unique_ptr<int>> v;
    v.push_back(move(a));
    v.push_back(move(b));
    unique_ptr<int> p = move(v.back());
    v.pop_back();
    for (int i = 0; i < v.size(); ++i)
        cout << *v[i] << endl;
    return 0;
}
