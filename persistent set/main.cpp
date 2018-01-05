#include "persistent_set.h"
#include <set>
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
    auto it = s.begin();
    while (it != s.end()) {
        std::cout << "while (it != s.end())\n";
        std::cout << *it++ << '\n';
    }
    s.erase(s.begin());
    s.print();
    auto last = s.end();
    last--;
     s.erase(last);
    s.print();
    auto b2 = s.begin();
    auto b3 = b2;
    ++b3;
    ++b3;
    --b3;
    --b3;
    std::cout << "b2 = " << *b2 << "\nb3 = " << *b3 << '\n';
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

template <template < typename > class ptr_t>
void test_2() {
    persistent_set<int, ptr_t> s;
    s.insert(4);
    s.erase(s.begin());
}


int main(int argc, char** agrv) {
//    std::cout << "bow-wow!!!\n";
//    test_2<my_shared_ptr>();
//     test_2<my_linked_ptr>();
     ::testing::InitGoogleTest(&argc, agrv);
     return RUN_ALL_TESTS();
//    return 0;
}
