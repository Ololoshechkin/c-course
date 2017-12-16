#ifndef UNIT_T_V
#define UNIT_T_V

#include "persistent_set.h"
#include "linked_ptr.h"
#include "shared_ptr.h"
#include <vector>
#include <string>
#include <set>
#include <iostream>

struct smth {
    int var;
    smth(int var) : var(var) {}
    smth() = delete;
    smth(smth const& rhs) {
        var = rhs.var;
    }
    smth(smth&& rhs) noexcept {
        var = rhs.var;
    }
    bool operator<(smth const& rhs) const {
        return var < rhs.var;
    }
    bool operator==(smth const& rhs) const {
        return var == rhs.var;
    }
    friend std::ostream& operator<<(std::ostream& out, smth s) {
        out << s.var;
        return out;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> v) {
    for (T x : v)
        out << x << ' ';
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, std::set<T> v) {
    for (T x : v)
        out << x << ' ';
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, persistent_set<T> v) {
    for (auto it : v)
        out << *it << ' ';
    return out;
}
//
//template <typename T>
//std::ostream& operator << (std::ostream& out, T v) {
//    if constexpr (std::is_same_v<T, std::string>) {
//        out << v;
//    } else if (std::is_same_v<T, const char*>) {
//        out << v;
//    } else if (std::is_same_v<T, std::vector<int>>) {
//        for (auto it : v) {
//            out << it << " ";
//        }
//    } else if (std::is_same_v<T, std::vector<smth>>) {
//        for (auto it : v) {
//            out << "smth ";
//        }
//    } else if (std::is_same_v<T, std::set<smth>>) {
//        for (auto it : v) {
//            out << "smth ";
//        }
//    } else if (std::is_same_v<T, std::set<int>>) {
//        for (auto it : v) {
//            out << *it << " ";
//        }
//    } else if (std::is_same_v<T, persistent_set<smth>>) {
//        for (auto it : v) {
//            out << "smth ";
//        }
//    } else if (std::is_same_v<T, persistent_set<int>>) {
//        for (auto it : v) {
//            out << *it << " ";;
//        }
//    }
//    return out;
//}


struct test_t {
    std::string t_set, t_name;
    std::function<void(test_t*)> tst;
    bool passed = true;
    test_t(std::string t_set, std::string t_name, std::function<void(test_t*)> tst)
    : t_set(t_set), t_name(t_name), tst(tst)
    {}
    void test() {
        tst(this);
        if (passed)
            std::cout << "[" << t_set << "]" << " [" << t_name << "] : passed\n";

    }
    template <typename A, typename B>
    void expect_eq(A a, B b) {
        if (a != b) {
            std::cout << "[" << t_set << "]" << " [" << t_name << "] : assertion failed (";
            std::cout << a << " != " << b << ")\n";
            passed = false;
        } else {
            std::cout << "[" << t_set << "]" << " [" << t_name << "] : assertion passed (";
            std::cout << a << " == " << b << ")\n";
        }
    }
};

std::vector<test_t> tests;

void add_test(test_t t) {
    tests.push_back(t);
}

#define TEST(a, b, c) add_test(test_t(a, b, c))
#define EXPECT_EQ(a, b) t->expect_eq(a, b)
#define fun [=](test_t* t)

template <typename T>
std::vector<T> vec(persistent_set<T> const& s) {
    std::vector<T> res;
    for (auto it = s.begin(); it != s.end(); ++it) {
        res.push_back(*it);
    }
    return res;
}

template < typename Set >
std::vector < std::vector < int > > test(std::string const& msg) {
    auto tt = clock();
    srand(1);
    std::vector < Set > ss(10000000);
    for (int i = 0; i < 256; ++i) {
        int r = rand() & 7;
        if (r == 0) {
            ss[rand() & 255] = ss[rand() & 255];
        } else if (r <= 3) {
            ss[rand() & 255].insert(rand() & 16383);
        } else {
            int j = rand() & 255;
            auto it = ss[j].find(rand() & 16383);
            if (it != ss[j].end())
                ss[j].erase(it);
        }
    }
    std::vector < std::vector < int > > a(256);
    for (int i = 0; i < 256; ++i)
        for (int x : ss[i])
            a[i].push_back(x);
    std::cout << msg << " " << 1.*(clock() - tt) / CLOCKS_PER_SEC << "\n";
    return a;
}

void test_all() {
    TEST("test_set", "insert", fun {
        persistent_set<int> s;
        s.insert(32);
        s.insert(33);
        EXPECT_EQ(std::vector<int>({32, 33}), vec(s));
    });

    TEST("test_set", "insert_10_elements", fun {
        persistent_set<int> s;
        for (int i = 0; i < 5; i++) {
            s.insert(i);
        }
        for (int j = 9; j >= 5; j--) {
            s.insert(j);
        }
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
    });

    TEST("test_set", "copy", fun {
        persistent_set<int> s;
        s.insert(1);
        persistent_set<int> p(s);
        p.insert(2);
        EXPECT_EQ(std::vector<int>({ 1 }), vec(s));
        EXPECT_EQ(std::vector<int>({ 1, 2 }), vec(p));
    });

    TEST("test_set", "copy2", fun {
        persistent_set<int> s;
        s.insert(12);
        persistent_set<int> p(s);
        s.insert(45);
        EXPECT_EQ(std::vector<int>({ 12, 45 }), vec(s));
        EXPECT_EQ(std::vector<int>({ 12 }), vec(p));
        p.insert(0);
        EXPECT_EQ(std::vector<int>({ 12, 45 }), vec(s));
        EXPECT_EQ(std::vector<int>({ 0, 12 }), vec(p));
    });

    TEST("test_set", "insert_and_copy", fun {
        persistent_set<int> s;
        s.insert(4);
        s.insert(5);
        s.insert(7);
        s.insert(6);
        s.insert(1);
        s.insert(2);
        s.insert(8);
        s.insert(3);
        s.insert(0);
        s.insert(9);
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
        persistent_set<int> p(s);
        s.insert(100);
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100 }), vec(s));
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(p));
    });
    
    TEST("test_set", "erase0", fun {
        persistent_set<int> s;
        s.insert(4);
        s.erase(s.begin());
        EXPECT_EQ(std::vector<int>({}), vec(s));
    });

    TEST("test_set", "erase", fun {
        persistent_set<int> s;
        EXPECT_EQ(std::vector<int>({ }), vec(s));
        s.insert(4);
        EXPECT_EQ(std::vector<int>({ 4 }), vec(s));
        s.insert(5);
        EXPECT_EQ(std::vector<int>({ 4, 5 }), vec(s));
        s.insert(7);
        EXPECT_EQ(std::vector<int>({ 4, 5, 7 }), vec(s));
        s.insert(6);
        EXPECT_EQ(std::vector<int>({ 4, 5, 6, 7 }), vec(s));
        s.insert(1);
        EXPECT_EQ(std::vector<int>({ 1, 4, 5, 6, 7 }), vec(s));
        s.insert(2);
        EXPECT_EQ(std::vector<int>({ 1, 2, 4, 5, 6, 7 }), vec(s));
        s.insert(8);
        EXPECT_EQ(std::vector<int>({ 1, 2, 4, 5, 6, 7, 8 }), vec(s));
        s.insert(3);
        EXPECT_EQ(std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8 }), vec(s));
        s.insert(0);
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), vec(s));
        s.insert(9);
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
        s.erase(s.begin());
        EXPECT_EQ(std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
        s.erase(s.find(5));
        EXPECT_EQ(std::vector<int>({ 1, 2, 3, 4, 6, 7, 8, 9 }), vec(s));
        s.erase(s.find(3));
        EXPECT_EQ(std::vector<int>({ 1, 2, 4, 6, 7, 8, 9 }), vec(s));
        s.erase(s.find(7));
        EXPECT_EQ(std::vector<int>({ 1, 2, 4, 6, 8, 9 }), vec(s));
        s.erase(s.find(1));
        EXPECT_EQ(std::vector<int>({ 2, 4, 6, 8, 9 }), vec(s));
        s.erase(s.find(8));
        EXPECT_EQ(std::vector<int>({ 2, 4, 6, 9 }), vec(s));
        s.erase(s.find(9));
        EXPECT_EQ(std::vector<int>({2, 4, 6}), vec(s));
        s.erase(s.find(4));
        EXPECT_EQ(std::vector<int>({ 2, 6 }), vec(s));
        s.erase(s.begin());
        EXPECT_EQ(std::vector<int>({ 6 }), vec(s));
        s.erase(s.begin());
        EXPECT_EQ(std::vector<int>({ }), vec(s));
        s.insert(100);
        EXPECT_EQ(std::vector<int>({ 100 }), vec(s));
        s.erase(s.find(100));
        EXPECT_EQ(std::vector<int>({}), vec(s));
    });

    TEST("test_set", "smth", fun {
        persistent_set<smth> s;
        s.insert(smth(2));
        s.insert(smth(1));
        s.erase(s.find(2));
        s.insert(smth(5));
        EXPECT_EQ(std::vector<smth>({1, 5}), vec(s));
        persistent_set<smth> p(s);
        p.insert(smth(0));
        EXPECT_EQ(std::vector<smth>({ 1, 5 }), vec(s));
        EXPECT_EQ(std::vector<smth>({ 0, 1, 5 }), vec(p));
        persistent_set<smth> q(s);
        s.insert(smth(8));
        EXPECT_EQ(std::vector<smth>({ 1, 5 }), vec(q));
        q = s;
        EXPECT_EQ(std::vector<smth>({ 1, 5, 8 }), vec(s));
        EXPECT_EQ(std::vector<smth>({ 1, 5, 8 }), vec(q));
        s.erase(s.find(8));
        EXPECT_EQ(std::vector<smth>({ 1, 5 }), vec(s));
        EXPECT_EQ(std::vector<smth>({ 1, 5, 8 }), vec(q));
    });

    TEST("test_linked_ptr", "copy_null", fun {
        linked_ptr<int> a;
        linked_ptr<int> b = a;
        linked_ptr<int> c = a;
        linked_ptr<int> d = a;
        linked_ptr<int> e = a;
        
        linked_ptr<int> f(new int(5));
        a = f;
        c = f;
        f = f;
        d = f;
        b = linked_ptr<int>(new int(6));
        c = b;
        b.swap(c);
        f = c;
        e = f;
        a = f;
        d = a;
        b = f;
    });
    
    TEST("test_set", "iterators", fun {
        persistent_set<int> s;
        s.insert(4);
        s.insert(5);
        s.insert(7);
        s.insert(6);
        s.insert(1);
        s.insert(2);
        s.insert(8);
        s.insert(3);
        s.insert(0);
        s.insert(9);
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
        for (int i = 0; i < 10; i++) {
            persistent_set<int> p = s;
            auto it = p.begin();
            for (int j = 0; j < i; j++) {
                it++;
            }
            EXPECT_EQ(*it, i);
        }
    });

    TEST("test_set", "decrease_end", fun {
        persistent_set<int> s;
        s.insert(4);
        s.insert(12);
        s.insert(1);
        persistent_set<int>::iterator it = s.end();
        it--;
        EXPECT_EQ(12, *it);
    });
    
    TEST("test_set", "erase2", fun {
        persistent_set<int> s;
        s.insert(4);
        s.insert(5);
        s.insert(7);
        s.insert(6);
        s.insert(1);
        s.insert(2);
        s.insert(8);
        s.insert(3);
        s.insert(0);
        s.insert(9);
        EXPECT_EQ(std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
        persistent_set<int> p;
        for (int i = 0; i < 10; i++) {
            p = s;
            auto it = p.begin();
            for (int j = 0; j < i; j++) {
                it++;
            }
            p.erase(it);
            std::vector<int> ans({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            ans.erase(ans.begin() + i);
            std::cerr << "vec(p) : " << vec(p) << '\n';
            EXPECT_EQ(ans, vec(p));
        }
    });

//    TEST("test_set", "random", fun {
//        auto r1 = test<persistent_set<int, shared_ptr>>("shared_ptr");
//        auto r2 = test<persistent_set<int, linked_ptr>>("linked_ptr");
//        EXPECT_EQ(r1, r2);
//        auto r3 = test<std::set<int>>("std::set  ");
//        EXPECT_EQ(r2, r3);
//    });
    for (auto t : tests) {
        t.test();
    }
}

#endif /* UNIT_T_V */

