//
//  main.cpp
//  deque
//
//  Created by Vadim on 01.07.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include "deque.h"
using namespace std;

void sashas_test()
{
    cout << "sashas :\n";
    deque<int> q;
    for (int i = 0; i < 10; ++i)
        q.push_back(i);
    for (int i = 0; i < 10; ++i)
        q.pop_back();
    q.push_back(1);
    for (int i = 10; i < 20; ++i) {
        q.insert(q.begin() + 1, i);
        for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
            cout << *it << ' ';
        cout << '\n' << '\n';
    }
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
        cout << *it << ' ';
    cout << '\n' << '\n';
}

void pf()
{
    cout << "push front :\n";
    deque<int> q;
    for (int i = 0; i < 10; ++i)
        q.push_front(i);
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
        cout << *it << ' ';
    cout << endl << endl;
}

void swap_it()
{
    cout << "swap iter :\n";
    deque<int> q1, q2;
    for (int i = 1; i <= 10; ++i)
        q1.push_back(i);
    q2.push_back(11);
    deque<int>::const_iterator beg1 = q1.begin(), end1 = q1.end();
    deque<int>::const_iterator beg2 = q2.begin(), end2 = q2.end();
    swap(q2, q1);
    cout << "q1 : " << endl;
    for (deque<int>::const_iterator it = beg1; it != end1; ++it)
        cout << *it << ' ';
    cout << "\nq2 : " << endl;
    for (deque<int>::const_iterator it = beg2; it != end2; ++it)
        cout << *it << ' ';
    cout << endl << endl;
}

int main(int argc, const char * argv[]) {
    sashas_test();
    pf();
    swap_it();
    cout << "main :\n";
    deque<int> q;
    for (int i = 0; i < 20; ++i)
        q.push_back(i);
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it)
        cout << *it << ' ';
    q.insert(q.begin() + 3, 100000);
    q.insert(q.begin() + 17, 99999);
    cout << '\n' << '\n';
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it)
        cout << *it << ' ';
    q.erase(q.begin());
    q.erase(q.begin() + 10);
    q.erase(q.begin() + 15);
    cout << '\n' << '\n';
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it)
        cout << *it << ' ';
    deque<int> q2;
    q2 = q;
    cout << '\n' << '\n';
    for (deque<int>::iterator it = q2.begin(); it != q2.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q2.rbegin(); it != q2.rend(); ++it)
        cout << *it << ' ';
    return 0;
}
