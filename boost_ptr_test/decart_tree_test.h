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

template<typename ptr>
ptr& arg(std::enable_if_t<std::is_copy_constructible_v<ptr>, ptr&> p) {
	return p;
}

template<typename ptr>
ptr&& arg(std::enable_if_t<!std::is_copy_constructible_v<ptr>, ptr&> p) {
	return std::move(p);
}

#define sz(v) (v.get() ? v->size : 0)
#define index(v) ((v->l.get() ? v->l->size : 0) + 1)

template <template<typename> class smart_ptr, typename T>
struct decart_tree_test : public abstract_test {
protected:
	void test_impl(int test_number) {
		treap_array t;
		int max_cnt = BIG_CONST * test_number;
		for (int i = 0; i < max_cnt; ++i)
			t.push_back(i);
		for (int i = 0; i < max_cnt; ++i) {
			int index = rand() % max_cnt + 1;
			t.insert(index, i);
		}
		for (int i = 0; i < max_cnt; ++i) {
			int index = t.size() + 1;
			t.erase(index);
		}
	}
private:
	struct treap_array {
		void push_back(T value) {
			root = merge(arg<Node>(root), Node(new node(value)));
		}
		void insert(int index, T value) {
			root = insert(arg<Node>(root), index, value);
		}
		void erase(int index) {
			root = erase(arg<Node>(root), index);
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
				l->r = merge(arg<Node>(l->r), arg<Node>(r));
				return upd(arg<Node>(l->r));
			} else {
				r->l = merge(arg<Node>(l), arg<Node>(r->l));
				return upd(arg<Node>(r));
			}
		}
		
		typedef std::pair<Node, Node> split_t;
		split_t split(Node t, int k) {
			if (!t.get()) return { node::null(), node::null() };
			if (index(t) <= k) {
				split_t ans = split(arg<Node>(t->r), k - index(t));
				t->r = arg<Node>(ans.first);
				ans.first = upd(arg<Node>(t));
				return ans;
			} else {
				split_t ans = split(arg<Node>(t->l), k);
				t->l = arg<Node>(ans.second);
				ans.second = upd(arg<Node>(t));
				return ans;
			}
		}
		Node insert(Node t, int i, T x) {
			Node n = Node(new node(x));
			if (!t.get())
				return n;
			split_t p = split(arg<Node>(t), i);
			return merge(merge(arg<Node>(p.first), arg<Node>(n)), arg<Node>(p.second));
		}
		Node erase(Node t, int pos) {
			if (sz(t) < pos)
				return node::null();
			split_t p = split(arg<Node>(t), pos);
			split_t p0 = split(arg<Node>(p.first), pos - 1);
			return merge(arg<Node>(p0.first), arg<Node>(p.second));
		}
	};
};

#endif /* decart_tree_test_h */