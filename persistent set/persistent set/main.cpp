#include "persistent_set.h"
#include <iostream>
#include "shared_ptr.h"
#include "linked_ptr.h"
#include <set>
#include <vector>
#include "unit_test.h"

template<template <typename> class smart_ptr>
void test_1() {
    persistent_set<int, smart_ptr> s;
    s.insert(1);
    s.print();
    s.insert(2);
    s.print();
    s.insert(-1);
    s.print();
    s.insert(3);
    s.print();
    s.insert(0);
    s.print();
    s.insert(-5);
    s.print();
    s.insert(-7);
    s.print();
    s.insert(100);
    s.print();
    s.erase(s.begin());
    s.print();
    auto last = s.end();
    last--;
    s.erase(last);
    s.print();
    for (auto it = s.begin(); it != s.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
    for (auto it = s.end(); ; --it) {
        if (it != s.end())
            std::cout << *it << ' ';
        if (it == s.begin()) break;
    }
    std::cout << std::endl << std::endl;
}

int main() {
    test_1<shared_ptr>();
    test_1<linked_ptr>();
    test_all();
    return 0;
}
