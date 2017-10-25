//
//  main.cpp
//  lectureDecltypeAuto
//
//  Created by Vadim on 07/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int f() {
    return 0;
}

template <typename T, typename ...Args>
int f(T x, Args... args) {
    return 1 + f(args...);
}

template <typename ...Args>
decltype(f(forward<Args>(declval<Args>())...)) g(Args&&... args) {
    return f(forward<Args>(args)...);
}

int one = 1;
int& int_ref_f() {
    return one;
}
int int_f() {
    return 2;
}

struct any {
    any();
    any(any const& other) {
        ptr = other.ptr;
        deleter = other.deleter;
    }
    template<typename T>
    any(T val) : ptr(new T(val)), deleter(&do_delete<T>) {}
    any* operator = (any const& other) {
        any tmp = other;
        return this;
    }
    ~any() {
        deleter(ptr);
    }
private:
    void* ptr;
    
    typedef void (*deleter_t)(void*);
    deleter_t deleter;
    
    template<typename T>
    static void do_delete(void* t_ptr) {
        delete (T*)t_ptr;
    }
};

struct any2 {
    struct concept {
        virtual ~concept() {}
    };
    template <typename T>
    struct impl: concept {
        T val;
        impl(T val): val(val) {}
    };
    template <typename T>
    any2(T val) : ptr(new impl<T>(val)) {}
private:
    unique_ptr<concept> ptr;
};

int main(int argc, const char * argv[]) {
    cout << g(1, 2, 3, 4, 5) << endl;
    auto a = 5; // int
    auto b = int_f(); // int
    auto c = int_ref_f(); // int&
    //auto& d = int_f();  - error!!!
    auto&& x = int_ref_f(); // int& , since     && x &   <=>  &
    auto&& y = int_f(); // int&&
    vector<int> v = {1, 2, 3, 4, 5};
    for (auto cur : v) {
        cout << cur << ' ';
        cur++;
    }
    cout << endl; // 1 2 3 4 5
    for (auto cur : v) {
        cout << cur << ' ';
        cur++;
    }
    cout << endl; // 1 2 3 4 5, тк. auto cur : v имеет тип int (copy)
    map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    for (pair<int, int> const& e: m) { //Loop variable 'e' has type 'const pair<int, int> &' but is initialized with type 'value_type' (aka 'pair<const int, int>') resulting in a copy
        cout << e.first << ' ' << e.second<< '\n';
    }
    auto lam = [](int x) {return x + 1;};
    cout << lam(100) << endl;
    int n;
    vector<int> gr[10];
    bool used[10];
    function<void(int)> dfs = [&](int v) {
        if (used[v]) return;
        used[v] = 1;
        for (int u: gr[v]) dfs(u);
    };
    any var = 1231;
    any2 var2 = "keker";
    string ︴= "😀😀😀😀😀😀";
    cout << ︴ << '\n';
    return 0;
}
