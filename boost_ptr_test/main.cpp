#include <iostream>
// #include <boost/intrusive_ptr.h>
#include "intrusive_ptr.h"
#include "alloc_dealloc_test.h"
#include "equasion_and_copy_test.h"
#include "decart_tree_test.h"
#include "linked_ptr.h"
#include <cstdio>

using namespace std;
using namespace boost;

constexpr int OPERATIONS_COUNT = 5000000;

uint64_t maxOf()
{
	return 0;
}

template<typename... Rest_T>
uint64_t maxOf(uint64_t first, Rest_T&& ... rest)
{
	return max(first, maxOf(rest...));
}

uint64_t middle(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	return (a + b + c + d) >> 2;
}

void print_constants(uint64_t benchmark_linked,
                     uint64_t benchmark_shared,
                     uint64_t benchmark_intrusive,
                     uint64_t benchmark_unique,
                     bool new_width = true)
{
	printf("real linked = %lld;\n"
			       "real shared = %lld;\n"
			       "real intrusive = %lld;\n"
			       "real unique = %lld;\n",
	       benchmark_linked / OPERATIONS_COUNT,
	       benchmark_shared / OPERATIONS_COUNT,
	       benchmark_intrusive / OPERATIONS_COUNT,
	       benchmark_unique / OPERATIONS_COUNT
	);
	if (new_width) {
		printf("real bench_width = %lld.0;\nreal max_height = %lld;\n\n"
				       "real linked_offset = bench_width;\n"
				       "real shared_offset = 2 * bench_width;\n"
				       "real intrusive_offset = 3 * bench_width;\n"
				       "real unique_offset = 4 * bench_width;\n"
				       "real label_offset = (shared_offset - linked_offset) / 2.0;\n"
				       "\n"
				       "size(20cm,0);\n",
		       middle(
				       benchmark_linked,
				       benchmark_shared,
				       benchmark_intrusive,
				       benchmark_unique
		       ) / OPERATIONS_COUNT,
		       maxOf(
				       benchmark_linked,
				       benchmark_shared,
				       benchmark_intrusive,
				       benchmark_unique
		       ) / OPERATIONS_COUNT
		);
	}
}

constexpr const char* LINKED_NAME = "$linked\\underline{\\hspace{0.3cm}}ptr$";
constexpr const char* SHARED_NAME = "$std::shared\\underline{\\hspace{0.3cm}}ptr$";
constexpr const char* INTRUISIVE_NAME = "$boost::intruisive\\underline{\\hspace{0.3cm}}ptr$";
constexpr const char* UNIQUE_NAME = "$std::unique\\underline{\\hspace{0.3cm}}ptr$";

void print_labels(const char* name1, const char* name2, const char* name3, const char* name4, const char* pen_color)
{
	printf(
			"label(\"%s\", (linked_offset - label_offset, linked), %s);\n"
					"label(\"%s\", (shared_offset - label_offset, shared), %s);\n"
					"label(\"%s\", (intrusive_offset - label_offset, intrusive), %s);\n"
					"label(\"%s\", (unique_offset - label_offset, unique), %s);\n",
			name1, pen_color, name2, pen_color, name3, pen_color, name4, pen_color
	);
}

void print_middle_part(const char* color1, const char* color2, const char* color3, const char* color4)
{
	printf("path lin = box((0,0), (linked_offset,linked));\n"
			       "fill(lin, %s);\n"
			       "\n"
			       "path sha = box((linked_offset,0), (shared_offset,shared));\n"
			       "fill(sha, %s);\n"
			       "\n"
			       "path intr = box((shared_offset,0), (intrusive_offset,intrusive));\n"
			       "fill(intr, %s);\n"
			       "\n"
			       "path uniq = box((intrusive_offset,0), (unique_offset,unique));\n"
			       "fill(uniq, %s);\n",
	       color1, color2, color3, color4
	);
}

void print_name(const char* name)
{
	printf("label(\"%s\", (bench_width * 2.0, max_height * 1.1));\n", name);
}


void print_code(const char* name,
                uint64_t benchmark_linked,
                uint64_t benchmark_shared,
                uint64_t benchmark_intrusive,
                uint64_t benchmark_unique)
{
	printf("settings.outformat = \"pdf\";\n\n");
	print_constants(benchmark_linked, benchmark_shared, benchmark_intrusive, benchmark_unique);
	print_middle_part("green", "blue", "magenta", "red");
	print_labels(LINKED_NAME, SHARED_NAME, INTRUISIVE_NAME, UNIQUE_NAME, "black");
	print_name(name);
}

void print_extra_for_memory_allocs(uint64_t benchmark_linked,
                                   uint64_t benchmark_shared,
                                   uint64_t benchmark_intrusive,
                                   uint64_t benchmark_unique)
{
	print_constants(benchmark_linked, benchmark_shared, benchmark_intrusive, benchmark_unique, false);
	print_middle_part("black", "black", "black", "black");
	print_labels("heap allocs", "heap allocs", "heap allocs", "heap allocs", "white");
}

struct my_int
{
	int value;
	int cnt;
	
	my_int(int value = 0) : value(value), cnt(1) {}
	
	operator int() const
	{
		return value;
	}
};

template<typename T>
using my_unique_ptr = unique_ptr<T, default_delete<T>>;

void bad_arg_report()
{
	cout << R"(please, type ONE argument : "alloc" | "copy" | "move" | "real"(decart treap))";
}

int main(int argc, const char* argv[])
{
	if (argc < 2) {
		bad_arg_report();
		return 0;
	}
	if (strcmp(argv[1], "alloc") == 0) {
		print_code("allocation/deallocation benchmark : ",
		           alloc_dealloc_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
		           alloc_dealloc_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
		           alloc_dealloc_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
		           alloc_dealloc_benchmark<my_unique_ptr, int>(OPERATIONS_COUNT)
		);
		uint64_t alloc_time_int = raw_alloc_benchmark<int>(OPERATIONS_COUNT);
		uint64_t alloc_time_my_int = raw_alloc_benchmark<my_int>(OPERATIONS_COUNT);
		print_extra_for_memory_allocs(
				alloc_time_int,
				alloc_time_int * 2,
				alloc_time_my_int,
				alloc_time_int
		);
	}
	else if (strcmp(argv[1], "copy constructor benchmark : ") == 0) {
		print_code("copy",
		           copy_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
		           copy_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
		           copy_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
		           0ll
		);
	}
	else if (strcmp(argv[1], "std::move benchmark : ") == 0) {
		print_code("std::move",
		           move_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
		           move_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
		           move_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
		           move_benchmark<my_unique_ptr, int>(OPERATIONS_COUNT)
		);
	}
	else if (strcmp(argv[1], "real usecase (decart treee) benchmark : ") == 0) {
		print_code("decart treap",
		           decart_treap_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
		           decart_treap_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
		           decart_treap_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
		           decart_treap_benchmark<my_unique_ptr, int>(OPERATIONS_COUNT)
		);
	}
	else {
		bad_arg_report();
	}
	return 0;
}
