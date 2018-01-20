#include <iostream>
#include <boost/smart_ptr.hpp>
#include "alloc_dealloc_test.h"
#include "equasion_and_copy_test.h"
#include "decart_tree_test.h"
#include "linked_ptr.h"
#include <cstdio>

using namespace std;
using boost::intrusive_ptr;

constexpr int OPERATIONS_COUNT = 5000000;

void define_vars()
{
	std::cout << "settings.outformat = \"pdf\";\n"
			"real max_height = 20.0;\n"
			"real bench_width = 3.0;\n"
			"\n"
			"real linked;\n"
			"real shared;\n"
			"real intrusive;\n"
			"real unique;\n"
			"real linked_disp;\n"
			"real shared_disp;\n"
			"real intrusive_disp;\n"
			"real unique_disp;\n"
			"\n"
			"real arrow_offset = bench_width;\n"
			"real point_offset = arrow_offset * 2 / 3;\n"
			"real linked_offset = arrow_offset + bench_width;\n"
			"real shared_offset = arrow_offset + 2 * bench_width;\n"
			"real intrusive_offset = arrow_offset + 3 * bench_width;\n"
			"real unique_offset = arrow_offset + 4 * bench_width;\n"
			"\n"
			"real label_offset = (shared_offset - linked_offset) / 2.0;\n"
			"real label_delta;\n"
			"\n"
			"real axis_scale = max_height / 10.0;\n"
			"\n"
			"real disp_eps = bench_width / 20.0;\n"
			"\n"
			"size(20cm,0);\n";
}

void define_functions()
{
	std::cout << "void draw_axis(real alpha) {\n"
			"\tdraw((arrow_offset / 2, 0) -- (arrow_offset / 2, max_height * 1.01),arrow=Arrow);\n"
			"\treal dy = arrow_offset / 10;\n"
			"\tfor (real i = 0; i < max_height; i += axis_scale) {\n"
			"\t\tdraw((arrow_offset / 2 - dy, i) -- (arrow_offset / 2 + dy, i));\n"
			"\t\tlabel(\n"
			"\t\t\tscale(0.5) * (\"\" + string((int)(i * alpha)) + \"\"),\n"
			"\t\t\tposition=(arrow_offset / 2 + dy, (int)(i)),\n"
			"\t\t\tblack,\n"
			"\t\t\talign=-W\n"
			"\t\t);\n"
			"\t}\n"
			"}\n"
			"\n"
			"void draw_exact_values(real offset = 0.0, real l, real s, real i, real u) {\n"
			"\treal[] exact_values = { l, s, i, u };\n"
			"\treal[] values = { linked, shared, intrusive, unique };\n"
			"\treal[] offsets = { linked_offset, shared_offset, intrusive_offset, unique_offset };\n"
			"\tfor (int i = 0; i < 4; ++i) {\n"
			"\t\tlabel(\n"
			"\t\t\tscale(0.5) * (\"\" + string(exact_values[i]) + \"\"),\n"
			"\t\t\t(offset + offsets[i] - bench_width / 2, values[i] + label_delta / 2),\n"
			"\t\t\tblack\n"
			"\t\t);\n"
			"\t}\n"
			"}\n"
			"\n"
			"void draw_boxes(real offset) {\n"
			"\treal[] offsets = { arrow_offset, linked_offset, shared_offset, intrusive_offset, unique_offset };\n"
			"\treal[] values = { linked, shared, intrusive, unique };\n"
			"\tpen[] pens = { deepgreen, royalblue, magenta, heavyred };\n"
			"\tfor (int i = 0; i < 4; ++i) {\n"
			"\t\tfill(box((offset + offsets[i], 0), (offset + offsets[i + 1], values[i])), pens[i]);\n"
			"\t}\n"
			"}\n"
			"\n"
			"void draw_boxes_darken(real offset) {\n"
			"\treal[] offsets = { arrow_offset, linked_offset, shared_offset, intrusive_offset, unique_offset };\n"
			"\treal[] values = { linked, shared, intrusive, unique };\n"
			"\tpen[] pens = { darkgreen, darkblue, darkmagenta, darkbrown };\n"
			"\tfor (int i = 0; i < 4; ++i) {\n"
			"\t\tfill(\n"
			"\t\t\tbox(\n"
			"\t\t\t\t(offset + offsets[i], 0), \n"
			"\t\t\t\t(offset + offsets[i + 1], values[i])\n"
			"\t\t\t), \n"
			"\t\t\tpens[i]\n"
			"\t\t);\n"
			"\t}\n"
			"}\n"
			"\n"
			"void draw_disps(real offset) {\n"
			"\treal[] values = { linked, shared, intrusive, unique };\n"
			"\treal[] offsets = { arrow_offset, linked_offset, shared_offset, intrusive_offset };\n"
			"\treal[] disps = { linked_disp, shared_disp, intrusive_disp, unique_disp };\n"
			"\tfor (int i = 0; i < 4; ++i) {\n"
			"\t\tdraw(\n"
			"\t\t\t(offset + offsets[i], values[i]) \n"
			"\t\t\t-- (offset + offsets[i], values[i] + disps[i]) \n"
			"\t\t\t-- (offset + offsets[i] + disp_eps, values[i] + disps[i]) \n"
			"\t\t\t-- (offset + offsets[i] - disp_eps, values[i] + disps[i]) \n"
			"\t\t\t-- (offset + offsets[i], values[i] + disps[i])\n"
			"\t\t\t-- (offset + offsets[i], values[i] - disps[i])\n"
			"\t\t\t-- (offset + offsets[i] + disp_eps, values[i] - disps[i]) \n"
			"\t\t\t-- (offset + offsets[i] - disp_eps, values[i] - disps[i]) \n"
			"\t\t\t-- (offset + offsets[i], values[i] - disps[i])\n"
			"\t\t, gray);\n"
			"\t}\n"
			"}\n"
			"\n"
			"void print_map() {\n"
			"\tstring[] names = { \n"
			"\t\t\"linked\\underline{\\hspace{0.3cm}}ptr\", \n"
			"\t\t\"shared\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"intrusive\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"unique\\underline{\\hspace{0.3cm}}ptr\"\n"
			"\t};\n"
			"\tpen[] pens = { deepgreen, royalblue, magenta, heavyred };\n"
			"\treal dw = bench_width / 7, dw1 = 3.0 * dw;\n"
			"\treal x0 = arrow_offset, y0 = -4.0 * dw; \n"
			"\tfor (int i = 0; i < 4; ++i) {\n"
			"\t\tfill(box((x0, y0), (x0 + dw, y0 + dw)), pens[i]);\n"
			"\t\tlabel(\n"
			"\t\t\tscale(0.7) * names[i],\n"
			"\t\t\tposition=(x0 + dw, y0 + dw / 2),\n"
			"\t\t\tblack,\n"
			"\t\t\talign=-W\n"
			"\t\t);\n"
			"\t\ty0 -= dw1;\n"
			"\t}\n"
			"}\n"
			"\n"
			"void print_map_extra() {\n"
			"\tstring[] names = {\n"
			"\t\t\"linked\\underline{\\hspace{0.3cm}}ptr\", \n"
			"\t\t\"shared\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"intrusive\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"unique\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"heap allocation inside linked\\underline{\\hspace{0.3cm}}ptr\", \n"
			"\t\t\"heap allocation inside shared\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"heap allocation inside intrusive\\underline{\\hspace{0.3cm}}ptr\",\n"
			"\t\t\"heap allocation inside unique\\underline{\\hspace{0.3cm}}ptr\"\n"
			"\t};\n"
			"\tpen[] pens = { \n"
			"\t\tdeepgreen, royalblue, magenta, heavyred, \n"
			"\t\tdarkgreen, darkblue, darkmagenta, darkbrown\n"
			"\t};\n"
			"\treal dw = bench_width / 7, dw1 = 3.0 * dw;\n"
			"\treal x0 = arrow_offset, y0 = -4.0 * dw; \n"
			"\tfor (int i = 0; i < 8; ++i) {\n"
			"\t\tif (i < 4) {\n"
			"\t\t\tfill(box((x0, y0), (x0 + dw, y0 + dw)), pens[i]);\n"
			"\t\t\tlabel(\n"
			"\t\t\t\tscale(0.7) * names[i],\n"
			"\t\t\t\tposition=(x0 + dw, y0 + dw / 2),\n"
			"\t\t\t\tblack,\n"
			"\t\t\t\talign=-W\n"
			"\t\t\t);\n"
			"\t\t\ty0 -= dw1;\n"
			"\t\t} else {\n"
			"\t\t\tfill(box((x0 + bench_width, y0), (x0 + dw + bench_width, y0 + dw)), pens[i]);\n"
			"\t\t\tlabel(\n"
			"\t\t\t\tscale(0.7) * names[i],\n"
			"\t\t\t\tposition=(x0 + dw + bench_width, y0 + dw / 2),\n"
			"\t\t\t\tblack,\n"
			"\t\t\t\talign=-W\n"
			"\t\t\t);\n"
			"\t\t\ty0 -= dw1;\n"
			"\t\t}\n"
			"\t\tif (i == 3)\n"
			"\t\t\ty0 += dw1 * 4;\n"
			"\t}\n"
			"}\n"
			"\n"
			"void draw_bench(string bench_name, \n"
			"\t\t\t\treal l, real s, real i, real u,\n"
			"\t\t\t\treal dl, real ds, real di, real du,\n"
			"\t\t\t\treal offset = 0.0, real alpha = 1.0, bool is_alloc = false) {\n"
			"\tlinked = alpha * l;\n"
			"\tshared = alpha * s;\n"
			"\tintrusive = alpha * i;\n"
			"\tunique = alpha * u;\n"
			"\n"
			"\tlinked_disp = alpha * dl;\n"
			"\tshared_disp = alpha * ds;\n"
			"\tintrusive_disp = alpha * di;\n"
			"\tunique_disp = alpha * du;\n"
			"\n"
			"\tlabel_delta = 0.05 * max(max(linked, shared), max(intrusive, unique));\n"
			"\n"
			"\tdraw_exact_values(offset, l, s, i, u);\n"
			"\tdraw_boxes(offset);\n"
			"\tdraw_disps(offset);\n"
			"\tif (!is_alloc) {\n"
			"\t\tlabel(bench_name, (offset + bench_width * 2.5, max_height * 1.1));\n"
			"\t}\n"
			"}\n"
			"\n"
			"void draw_inits(real alpha = 1.0) {\n"
			"\tprint_map();\n"
			"\tdraw_axis(1.0 / alpha);\n"
			"}\n"
			"\n"
			"void draw_inits_alloc(real alpha = 1.0) {\n"
			"\tprint_map_extra();\n"
			"\tdraw_axis(1.0 / alpha);\n"
			"}\n"
			"void define_vals(\n"
			"\treal l, real s, real i, real u, \n"
			"\treal dl, real ds, real di, real du,\n"
			"\treal alpha\n"
			") {\n"
			"\tlinked = alpha * l;\n"
			"\tshared = alpha * s;\n"
			"\tintrusive = alpha * i;\n"
			"\tunique = alpha * u;\n"
			"\n"
			"\tlinked_disp = alpha * dl;\n"
			"\tshared_disp = alpha * ds;\n"
			"\tintrusive_disp = alpha * di;\n"
			"\tunique_disp = alpha * du;\n"
			"}\n";
}

void print_vararg() {}

template <typename T>
void print_vararg(T x) { std::cout << x; }

template <typename T1, typename T2, typename... Args>
void print_vararg(T1 arg0, T2 arg1, Args... args)
{
	std::cout << arg0 << ", ";
	print_vararg(arg1, args...);
}

template <typename... Args>
void call_function(string name, Args... args)
{
	std::cout << name + "(";
	print_vararg(args...);
	std::cout << ");\n";
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

template <typename T>
void intrusive_ptr_add_ref(T* m)
{
	m->cnt++;
}

template <typename T>
void intrusive_ptr_release(T* m)
{
	if (!(--m->cnt))
		delete m;
}

template <typename T>
using my_unique_ptr = unique_ptr<T, default_delete<T>>;

void bad_arg_report()
{
	cout << R"(please, type ONE argument : "alloc" | "copy" | "move" | "real"(decart treap))";
}

using std::shared_ptr;

int main(int argc, const char* argv[])
{
	if (argc < 2) {
		bad_arg_report();
		return 0;
	}
	if (strcmp(argv[1], "alloc") == 0) {
		freopen("alloc.asy", "w", stdout);
		define_vars();
		define_functions();
		auto l = alloc_dealloc_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
				s = alloc_dealloc_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
				i = alloc_dealloc_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
				u = alloc_dealloc_benchmark<my_unique_ptr, int>(OPERATIONS_COUNT);
		auto l2 = raw_alloc_benchmark<int>(OPERATIONS_COUNT),
				s2 = raw_alloc_benchmark<int>(OPERATIONS_COUNT) * 2,
				i2 = raw_alloc_benchmark<my_int>(OPERATIONS_COUNT),
				u2 = raw_alloc_benchmark<int>(OPERATIONS_COUNT);
		double alpha = 20.0 / max(max(l.res, s.res), max(i.res, u.res));
		call_function("draw_inits_alloc", alpha);
		call_function(
				"draw_bench",
				"\"allocation benchmark:\"",
				l.res, s.res, i.res, u.res,
				l.disp, s.disp, i.disp, u.disp,
				0.0, alpha, "true"
		);
		call_function("define_vals",
					  l2.res, s2.res, i2.res, u2.res,
					  l2.disp, s2.disp, i2.disp, u2.disp,
					  alpha
		);
		call_function("draw_boxes_darken", 0.0);
		call_function("draw_disps", 0.0);
	} else if (strcmp(argv[1], "copy_move") == 0) {
		freopen("copy_move.asy", "w", stdout);
		define_vars();
		define_functions();
		auto l = copy_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
				s = copy_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
				i = copy_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
				u = benchmark_res(0, 0);
		auto l2 = move_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
				s2 = move_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
				i2 = move_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
				u2 = move_benchmark<my_unique_ptr, int>(OPERATIONS_COUNT);
		double alpha1 = max(max(l.res, s.res), max(i.res, u.res));
		double alpha2 = max(max(l2.res, s2.res), max(i2.res, u2.res));
		double alpha = 20.0 / max(alpha1, alpha2);
		call_function("draw_inits", alpha);
		call_function(
				"draw_bench",
				"\"copy benchmark : \"",
				l.res, s.res, i.res, u.res,
				l.disp, s.disp, i.disp, u.disp,
				0.0,
				alpha
		);
		call_function(
				"draw_bench",
				"\"move benchmark : \"",
				l2.res, s2.res, i2.res, u2.res,
				l2.disp, s2.disp, i2.disp, u2.disp,
				"bench_width * 4.3",
				alpha
		);
	} else if (strcmp(argv[1], "real") == 0) {
		freopen("real.asy", "w", stdout);
		define_vars();
		define_functions();
		auto l = decart_treap_benchmark<linked_ptr, int>(OPERATIONS_COUNT),
				s = decart_treap_benchmark<shared_ptr, int>(OPERATIONS_COUNT),
				i = decart_treap_benchmark<intrusive_ptr, my_int>(OPERATIONS_COUNT),
				u = decart_treap_benchmark<my_unique_ptr, int>(OPERATIONS_COUNT);
		double alpha = 20.0 / max(max(l.res, s.res), max(i.res, u.res));
		call_function("draw_inits", alpha);
		call_function(
				"draw_bench",
				"\"real usecase (decart tree) benchmark : \"",
				l.res, s.res, i.res, u.res,
				l.disp, s.disp, i.disp, u.disp,
				0.0, alpha
		);
	} else {
		bad_arg_report();
	}
	return 0;
}
