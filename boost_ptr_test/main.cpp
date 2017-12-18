#include <iostream>
// #include <boost/intrusive_ptr.h>
#include "intrusive_ptr.h"
#include <memory.h>
#include "alloc_dealloc_test.h"
#include "equasion_and_copy_test.h"
#include "decart_tree_test.h"
#include <unordered_map>
#include <string>
#include "linked_ptr.h"
using namespace std;
using namespace boost;

typedef unordered_map<string, vector<double>> bench_t;

void print_bench(string name, bench_t benchmark) {
    cout << name << " : \n";
    for (auto bench : benchmark) {
        cout << "   " << bench.first << " : \n";
        for (double time : bench.second)
            cout << "   " << time << ' ';
        cout << '\n';
    }
}

int* new_int_array() {
    return new int[4];
}

struct my_int {
    int value;
    int cnt;
    my_int(int value = 0): value(value), cnt(1) {}
    operator int() const {
        return value;
    }
};

my_int* new_my_int_array() {
    return new my_int[4];
}

template <typename T>
using my_unique_ptr = unique_ptr<T, default_delete<T>>;

int main(int argc, const char * argv[]) {
    bench_t bench_linked, bench_shared, bench_unique, bench_intrusive;//, bench_row;

//    bench_row["alloc / dealloc"] = alloc_dealloc_test<
//        row_ptr,
//        int,
//        *new_int_array
//    >().get_benchmark();
//    
//    bench_row["copy / := "] = equasion_and_copy_test<
//        row_ptr,
//        int,
//        *new_int_array
//    >().get_benchmark();
//    
//    bench_row["decart tree usage"] = decart_tree_test<
//        row_ptr,
//        int
//    >().get_benchmark();
//    
//    print_bench("row", bench_row);
    
    bench_linked["alloc / dealloc"] = alloc_dealloc_test<
        linked_ptr,
        int,
        *new_int_array
    >().get_benchmark();
    
    bench_linked["copy / := "] = equasion_and_copy_test<
        linked_ptr,
        int,
        *new_int_array
    >().get_benchmark();
    
    bench_linked["decart tree usage"] = decart_tree_test<
        linked_ptr,
        int
    >().get_benchmark();
    
    print_bench("linked", bench_linked);

    bench_intrusive["alloc / dealloc"] = alloc_dealloc_test<
        intrusive_ptr,
        my_int,
        *new_my_int_array
    >().get_benchmark();

    bench_intrusive["copy / := "] = equasion_and_copy_test<
        intrusive_ptr,
        my_int,
        *new_my_int_array
    >().get_benchmark();

    bench_intrusive["decart tree usage"] = decart_tree_test<
        intrusive_ptr,
        my_int
    >().get_benchmark();

    print_bench("intrusive", bench_intrusive);
    
    bench_shared["alloc / dealloc"] = alloc_dealloc_test<
        shared_ptr,
        int,
        *new_int_array
    >().get_benchmark();

    bench_shared["copy / := "] = equasion_and_copy_test<
        shared_ptr,
        int,
        *new_int_array
    >().get_benchmark();

    bench_shared["decart tree usage"] = decart_tree_test<
        shared_ptr,
        int
    >().get_benchmark();

    bench_unique["alloc / dealloc"] = alloc_dealloc_test<
        my_unique_ptr,
        int,
        *new_int_array
    >().get_benchmark();

    bench_unique["copy / := "] = equasion_and_copy_test<
        my_unique_ptr,
        int,
        *new_int_array
    >().get_benchmark();

    bench_unique["decart tree usage"] = decart_tree_test<
        my_unique_ptr,
        int
    >().get_benchmark();

    print_bench("shared", bench_shared);
    print_bench("unique", bench_unique);
    return 0;
}
