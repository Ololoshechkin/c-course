//
//  decart_tree_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  copy_ptrright © 2017 Vadim. All rights reserved.
//

#ifndef decart_tree_test_h
#define decart_tree_test_h

#include "abstract_test.h"


#define sz(v) ((v).get() ? (v)->size : 0)
#define index(v) (((v)->l.get() ? (v)->l->size : 0) + 1)

template <template <typename> class smart_ptr, typename T>
struct treap_array {
	void push_back(T value) {
		root = merge(std::move(root), Node(new node(value)));
	}
	void insert(int index, T value) {
		root = insert(std::move(root), index, value);
	}
	void erase(int index) {
		root = erase(std::move(root), index);
	}
	int size() {
		return sz(root);
	}
private:
	struct node {
		typedef smart_ptr<node> Node;
		Node l, r;
		int size, y;
		T value;
		int cnt = 1;
		static Node null() {
			return Node(nullptr);
		}
		node(T value,
		     Node l = node::null(),
		     Node r = node::null()) :
				l(Node(l.get())), r(Node(r.get())), size(1), y(rand()), value(value)
		{}
	};
//        using node::Node;
	typedef smart_ptr<node> Node;
	Node root = node::null();
	template <typename Node>
	Node upd(Node v) {
		v->size = sz(v->l) + sz(v->r) + 1;
		return v;
	}
	Node merge(Node l, Node r) {
		if (!l.get()) return r;
		if (!r.get()) return l;
		if (l->y > r->y) {
			l->r = merge(std::move(l->r), std::move(r));
			return upd(std::move(l->r));
		} else {
			r->l = merge(std::move(l), std::move(r->l));
			return upd(std::move(r));
		}
	}
	
	typedef std::pair<Node, Node> split_t;
	split_t split(Node t, int k) {
		if (!t.get()) return { node::null(), node::null() };
		if (index(t) <= k) {
			split_t ans = split(std::move(t->r), k - index(t));
			t->r = std::move(ans.first);
			ans.first = upd(std::move(t));
			return ans;
		} else {
			split_t ans = split(std::move(t->l), k);
			t->l = std::move(ans.second);
			ans.second = upd(std::move(t));
			return ans;
		}
	}
	Node insert(Node t, int i, T x) {
		Node n = Node(new node(x));
		if (!t.get())
			return n;
		split_t p = split(std::move(t), i);
		return merge(merge(std::move(p.first), std::move(n)), std::move(p.second));
	}
	Node erase(Node t, int pos) {
		if (sz(t) < pos)
			return node::null();
		split_t p = split(std::move(t), pos);
		split_t p0 = split(std::move(p.first), pos - 1);
		return merge(std::move(p0.first), std::move(p.second));
	}
};

template <template <typename> class smart_ptr, typename T>
decltype(auto) decart_treap_benchmark(int operations_count) {
	return run_benchmark([operations_count]() {
		treap_array<smart_ptr, T> t;
		for (int i = 0; i < operations_count; ++i)
			t.push_back(i);
		for (int i = 0; i < operations_count; ++i) {
			int index = rand() % operations_count + 1;
			t.insert(index, i);
		}
		for (int i = 0; i < operations_count; ++i) {
			int index = t.size() + 1;
			t.erase(index);
		}
	}) / operations_count;;
};

#endif /* decart_tree_test_h */