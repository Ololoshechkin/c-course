//
//  main.cpp
//  metaprogramming_lecture
//
//  Created by Vadim on 11/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
using namespace std;

struct nil {};

template <typename Data, typename Next>
struct node {
    typedef Data data;
    typedef Next next;
};

template <typename List, typename Elem>
struct push_front {
    typedef node<Elem, List> type;
};

template <typename List, size_t N>
struct at {
    typedef typename at<typename List::next, N - 1>::type type;
};

template <typename List>
struct at<List, 0> {
    typedef typename List::data type;
};

template <typename List, typename Elem>
struct push_back {
    typedef node<typename List::data, typename push_back<typename List::next, Elem>::type> type;
};

template <typename Elem>
struct push_back<nil, Elem> {
    typedef node<Elem, nil> type;
};

template <typename List>
struct pop_front {
    typedef typename List::next type;
};


template <typename List>
struct pop_back {
    typedef node<
        typename List::data,
        typename pop_back<typename List::next>::type
    > type;
};

template <typename Data>
struct pop_back<node<Data, nil>> {
    typedef nil type;
};

template <typename UnhandledPrefix, typename RevSufix = nil>
struct reverse_list
{
    typedef typename reverse_list
    <
        typename UnhandledPrefix::next,
        typename push_front<RevSufix, typename RevSufix::data>::type
    >::type type;
};

template <typename List2>
struct reverse_list<nil, List2>
{
    typedef List2 type;
};

template <typename T>
T my_abs(T value) {
    if constexpr(std::is_signed_v<T>) {
        return value < 0 ? -value : value;
    } else {
        return value;
    }
}


int main(int argc, const char * argv[]) {
    cout << abs(-5) << endl;
    return 0;
}
