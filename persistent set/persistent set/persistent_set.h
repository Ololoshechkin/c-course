//
//  persistent_set.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef persistent_set_h
#define persistent_set_h

#include "my_shared_ptr.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>

template <typename T>
class std_shared_ptr {
public:
	std::shared_ptr<T> p;
	std_shared_ptr() : p(nullptr) {}
	std_shared_ptr(std::shared_ptr<T> p) : p(p) {}
	operator std::shared_ptr<T>() {
		return p;
	}
	template <typename... Args>
	static std_shared_ptr of(Args... args) {
		return std_shared_ptr(std::make_shared<T>(args...));
	}
	operator bool() const noexcept {
		return (bool)p;
	}
	T* operator->() noexcept {
		return p.get();
	}
	bool operator==(const std_shared_ptr& other) const noexcept {
		return p == other.p;
	}
	bool operator!=(const std_shared_ptr& other) const noexcept {
		return p != other.p;
	}
};

template <typename T, template <typename> class smart_ptr = std_shared_ptr>
class persistent_set {
private:
	struct node {
		typedef smart_ptr<node> Node;
		T value;
		Node left, right;
		bool operator == (node other) const noexcept {
			return left == other.left && right == other.right && value == other.value;
		}
		node(T const& value, Node left = Node(), Node right = Node())
				: value(value), left(left), right(right)
		{}
		node(T&& value, Node left = Node(), Node right = Node())
				: value(std::move(value)), left(left), right(right)
		{}
		Node the_least_child() const noexcept {
			return left ? left->the_least_child() : right->the_least_child();
		}
	};
	using Node = typename node::Node;
	Node root;
	
	Node copy(Node other) const {
		return Node::of(other->value, other->left, other->right);
	}
	
	void print(Node v) {
		if (!v) return;
		print(v->left);
		std::cout << " " << v->value << " ";
		print(v->right);
	}
public:
	
	void print() {
		print(root);
		std::cout << '\n';
	}
	// Bidirectional iterator.
	struct iterator {
		T const& operator*() const {
			Node n = path.back();
			return n->value;
		}
		iterator& operator++() {
			assert(!path.empty());
			if (cur_node()->right) {
				path.push_back(cur_node()->right);
				go_left();
			} else {
				while(true) {
					if (path.size() == 1 || last_is_left_son())
						break;
					path.pop_back();
				}
				path.pop_back();
			}
			return *this;
		}
		iterator operator++(int) {
			iterator res = *this;
			++*this;
			return res;
		}
		iterator& operator--() {
//	        std::cerr << "it--\n";
			if (is_end()) {
				path.push_back(root());
				go_right();
			} else {
				if (cur_node()->left) {
					path.push_back(cur_node()->left);
					go_right();
				} else {
					while(true) {
						assert(!path.empty());
						if (path.size() != 1 && !last_is_left_son())
							break;
						path.pop_back();
					}
					path.pop_back();
				}
			}
			return *this;
		}
		iterator operator--(int) {
			iterator res = *this;
			--*this;
			return res;
		}
		iterator(iterator const& other):
				s(other.s), path(other.path)
		{}
		void swap(iterator& other) {
			std::swap(s, other.s);
			std::swap(path, other.path);
		}
		iterator& operator=(iterator other) {
			auto tmp = other;
			swap(tmp);
			return *this;
		}
		bool operator==(iterator const& other) const  {
			// std::cerr << "==\n";
			return s == other.s && path == other.path;
		}
		bool operator!=(iterator const& other) const noexcept {
			return !(*this == other);
		}
	private:
		const persistent_set* s;
		std::vector<Node> path;
		Node root() const {
			return s->root;
		}
		iterator(const persistent_set* s, std::vector<Node> path)
				: s(s), path(path)
		{}
		bool is_end() const noexcept {
			return path.empty();
		}
		Node cur_node() const noexcept {
			return path.back();
		}
		Node cur_node_or_null() const noexcept {
			return path.empty() ? Node() : cur_node();
		}
		void go_left() noexcept {
			while (cur_node()->left)
				path.push_back(cur_node()->left);
		}
		void go_right() noexcept {
			while (cur_node()->right)
				path.push_back(cur_node()->right);
		}
		bool last_is_left_son() {
			return path[path.size() - 2]->left == cur_node();
		}
		friend persistent_set;
	};
	persistent_set()
	{}
	persistent_set(persistent_set const& other) 
			: root(other.root)
	{}
	void swap(persistent_set& other) {
		std::swap(root, other.root);
	}
	persistent_set& operator=(persistent_set const& rhs) {
		persistent_set tmp(rhs);
		swap(tmp);
		return *this;
	}
	iterator begin() const {
		if (root) {
			auto st = iterator(this, { root });
			st.go_left();
			return st;
		}
		return end();
	}
	iterator end() const {
		return iterator(this, {});
	}
	iterator last() const {
		iterator en = end();
		return --en;
	}
	// Поиск элемента.
	// Возвращает итератор на найденный элемент, либо end(), если элемент
	// с указанным значением отсутвует.
	iterator find(T const& newVal) {
		iterator found(this, {});
		auto cur = root;
		while (cur) {
			found.path.push_back(cur);
			if (newVal < cur->value)
				cur = cur->left;
			else if (cur->value < newVal)
				cur = cur->right;
			else
				return found;
		}
		return end();
	}
	// Вставка элемента.
	// 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
	//    на уже присутствующий элемент и false.
	// 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
	//    элемент и true.
	// Если вставка произведена, инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
	// std::pair<iterator, bool> insert(T newValue) {
	//     if (!root) {
	//         //std::cerr << "root==0\n";
	//         root = Node::of(std::move(newValue));
	//         return { iterator(this, { root }), true };
	//     }
	//     //std::cerr << "root!=0\n";
	//     auto res = iterator(this, { });
	//     //std::cerr << "res = iter\n";
	//     auto cur = root;
	//     //std::cerr << "cur = root\n";
	//     while (cur) {
	//         //std::cerr << "in while\n";
	//         res.path.push_back(cur);
	//         //std::cerr << "res <- cur\n";
	//         if (newValue < cur->value) {
	//             //std::cerr << "newValue < cur->value\n";
	//             if (!cur->left) {
	//                 //std::cerr << "!cur->left\n";
	//                 res.path.push_back(Node::of(std::move(newValue)));
	//                 break;
	//             }
	//             cur = cur->left;
	//         } else if (cur->value < newValue) {
	//             //std::cerr << "cur->value < newValue\n";
	//             if (!cur->right) {
	//                 //std::cerr << "!cur->right\n";
	//                 res.path.push_back(Node::of(std::move(newValue)));
	//                 //std::cerr << "res <- (Node::of(newValue)\n";
	//                 break;
	//             }
	//             cur = cur->right;
	//         } else return { res, false };
	//     }
	
	//     //std::cerr << "out of while\n";
	//     for (auto i = res.path.size() - 1; i > 0;) {
	//         //std::cerr << "for (" << i << ")\n";
	//         --i;
	//         Node v = res.path[i];
	//         //std::cerr << "Node v = res.path[i];\n";
	//         if (newValue < v->value)
	//             res.path[i] = Node::of(v->value, res.path[i + 1], v->right);
	//         else
	//             res.path[i] = Node::of(v->value, v->left, res.path[i + 1]);
	//     }
	//     //std::cerr << "out of for\n";
	//     root = res.path[0];
	//     //std::cerr << "return\n";
	//     return { res, true };
	// }
	
	
	std::pair<iterator, bool> insert(T newValue) {
		if (!root) {
//            std::cerr << "!root\n";
			root = Node::of(newValue);
			return { iterator(this, { root }), true };
		}
//        std::cerr << "root\n";
		auto found = find(newValue);
		if (found != end()) {
//            std::cerr << "found != end()\n";
			return { found, false };
		} else {
//            std::cerr << "found == end()\n";
			auto new_root = copy(root);
			auto cur = new_root, cur_old = root;
			std::vector<Node> path = { new_root };
			while (true) {
				if (!cur_old) break;
//                std::cerr << "val : " << cur_old->value << '\n';
				if (cur_old->value < newValue) {
					cur_old = cur_old->right;
					cur->right = cur_old ? copy(cur_old) : Node::of(newValue);
					cur = cur->right;
				} else {
					cur_old = cur_old->left;
					cur->left = cur_old ? copy(cur_old) : Node::of(newValue);
					cur = cur->left;
				}
				path.push_back(cur);
			}
			root = new_root;
			return { iterator(this, path), true };
		}
	}
	
	void erase(iterator it) {
		assert(!it.path.empty());
		auto last = it.cur_node();
		std::function<T(Node)> get_min = [&get_min](Node v) {
			return v->left ? get_min(v->left) : v->value;
		};
		std::function<Node(Node)> copy_path = [&copy_path](Node v) {
			return v->left ? Node::of(v->value, copy_path(v->left), v->right) : v->right;
		};
		Node cur_v = !last->left ? last->right :
		             !last->right ? last->left : Node::of(
				             get_min(last->right),
				             last->left,
				             copy_path(last->right)
		             );
		for (auto i = it.path.size() - 1; i > 0;) {
			Node parent = it.path[--i];
			if (parent->left == last)
				cur_v = Node::of(parent->value, cur_v, parent->right);
			else
				cur_v = Node::of(parent->value, parent->left, cur_v);
			last = parent;
		}
		root = cur_v;
	}
	
};

// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
// Сравнение с невалидным итератором не определено.
// Сравнение итераторов двух разных контейнеров не определено.
template <typename T>
bool operator==(typename persistent_set<T>::iterator it1, typename persistent_set<T>::iterator it2) {
	return it1.path == it2.path && it1.root == it2.root;
}

template <typename T>
bool operator!=(typename persistent_set<T>::iterator it1, typename persistent_set<T>::iterator it2) {
	return !(it1 == it2);
}



#endif /* persistent_set_h */
