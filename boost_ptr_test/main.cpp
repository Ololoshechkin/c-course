#include <iostream>
// #include <boost/intrusive_ptr.h>
#include "intrusive_ptr.h"
#include <memory>
#include "alloc_dealloc_test.h"
#include "equasion_and_copy_test.h"
#include "decart_tree_test.h"
#include <unordered_map>
#include <string>
#include "linked_ptr.h"
using namespace std;
using namespace boost;

typedef unordered_map<string, vector<std::chrono::high_resolution_clock::duration>> bench_t;

void print_bench(string name, bench_t benchmark) {
    cout << name << " : \n";
    for (auto bench : benchmark) {
        cout << "   " << bench.first << " : \n";
        for (auto time : bench.second)
            cout << "   " << chrono::duration_cast<chrono::duration<double>>(time).count() << ' ';
        cout << '\n';
    }
}

struct my_int {
    int value;
    int cnt;
    my_int(int value = 0): value(value), cnt(1) {}
    operator int() const {
        return value;
    }
};

template <typename T>
using my_unique_ptr = unique_ptr<T, default_delete<T>>;

int main(int argc, const char * argv[]) {
    bench_t bench_linked, bench_shared, bench_unique, bench_intrusive;//, bench_row;
	
//    bench_row["alloc / dealloc"] = alloc_dealloc_test<
//        row_ptr,
//        int,
//        *new_int_array
//    >().run_benchmark();
//    
//    bench_row["copy / := "] = copy_test<
//        row_ptr,
//        int,
//        *new_int_array
//    >().run_benchmark();
//    
//    bench_row["decart tree usage"] = decart_tree_test<
//        row_ptr,
//        int
//    >().run_benchmark();
//    
//    print_bench("row", bench_row);
    
    bench_linked["alloc / dealloc"] = alloc_dealloc_benchmark<linked_ptr, int>(10);
    bench_linked["copy / := "] = copy_benchmark<linked_ptr, int>(10);
	bench_linked["move"] = move_benchmark<linked_ptr, int>(10);
	bench_linked["decart tree usage"] = decart_treap_benchmark<linked_ptr, int>(10);
	
	print_bench("linked", bench_linked);
	
	bench_intrusive["alloc / dealloc"] = alloc_dealloc_benchmark<intrusive_ptr, my_int>(10);
	bench_intrusive["copy / := "] = copy_benchmark<intrusive_ptr, my_int>(10);
	bench_intrusive["move"] = move_benchmark<intrusive_ptr, my_int>(10);
	bench_intrusive["decart tree usage"] = decart_treap_benchmark<intrusive_ptr, my_int>(10);
	
    print_bench("intrusive", bench_intrusive);
	
	bench_shared["alloc / dealloc"] = alloc_dealloc_benchmark<shared_ptr, int>(10);
	bench_shared["copy / := "] = copy_benchmark<shared_ptr, int>(10);
	bench_shared["move"] = move_benchmark<shared_ptr, int>(10);
	bench_shared["decart tree usage"] = decart_treap_benchmark<shared_ptr, int>(10);
	
	print_bench("shared", bench_shared);
	
	bench_unique["alloc / dealloc"] = alloc_dealloc_benchmark<my_unique_ptr, int>(10);
	bench_unique["move"] = move_benchmark<my_unique_ptr, int>(10);
	bench_unique["decart tree usage"] = decart_treap_benchmark<my_unique_ptr, int>(10);
	
	print_bench("unique", bench_unique);

    return 0;
}
