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
#include "my_linked_ptr.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include "fast_rand.h"

template <typename T, template <typename> class smart_ptr = my_shared_ptr>
class persistent_set
{
private:
	struct abstract_node;
	struct node;

	struct abstract_node
	{
		typedef smart_ptr<abstract_node> AbstractNode;
		typedef smart_ptr<node> Node;
		typedef std::vector<node*> path_t;
		Node left;

		abstract_node(abstract_node const& other) noexcept
				: left(other.left) {}

		abstract_node(abstract_node&& other) noexcept
				: left(std::move(other.left)) {}

		explicit abstract_node(Node left) noexcept
				: left(std::move(left)) {}

		decltype(auto) path_to_with_first(T const& value)
		{
			auto sufix = std::move(path_to(value));
			std::vector<abstract_node*> p(sufix.size() + 1, nullptr);
			p[0] = this;
			for (size_t i = 0; i < sufix.size(); ++i)
				p[i + 1] = sufix[i];
			return p;
		}

		path_t path_to(T const& value)
		{
			path_t path;
			auto v = is_last() ? this->left.get() : this->as_node();
			while (v) {
				path.push_back(v);
				if (v->value < value) {
					v = v->right.get();
				} else if (value < v->value) {
					v = v->left.get();
				} else {
					break;
				}
			}
			return path;
		}

		virtual bool is_last() const noexcept
		{
			return true;
		}

		node* as_node()
		{
			return static_cast<node*>(this);
		}

		node const* as_node() const
		{
			return static_cast<node const*>(this);
		}

		virtual ~abstract_node() = default;

	};

	struct node : public abstract_node
	{
		using Node = typename abstract_node::Node;
		T value;
		Node right;

		bool operator==(node const& other) const noexcept
		{
			return this->left == other.left && right == other.right;
		}

		bool operator==(abstract_node const& other) const noexcept
		{
			return false;
		}

		explicit node(T const& value, Node left = Node(), Node right = Node()) noexcept(noexcept(T(value)))
				: abstract_node(std::move(left)),
				  right(std::move(right)),
				  value(value) {}

		bool is_last() const noexcept
		{
			return false;
		}

	};

	using AbstractNode = typename abstract_node::AbstractNode;
	using Node = typename abstract_node::Node;
	using path_t = typename abstract_node::path_t;

	AbstractNode root;

	Node merge(Node left, Node right)
	{
		if (!left) return right;
		if (!right) return left;
		if (rand_bit()) {
			left = Node::make_shared(left->value, left->left, merge(left->right, right));
			return left;
		} else {
			right = Node::make_shared(right->value, merge(left, right->left), right->right);
			return right;
		}
	}

	std::string n_spaces(size_t n) const {
		return std::string(n, ' ');
	}

	void print(Node v, size_t depth = 1) const
	{
		if (!v) {
			std::cout << n_spaces(depth) << "{}\n";
			return;
		}
		std::cout << n_spaces(depth) << "{\nvalue : " << v->value << "\nleft : \n";
		print(v->left, depth + 1);
		std::cout << n_spaces(depth) << "right : \n";
		print(v->right, depth + 1);
		std::cout << n_spaces(depth) << "}\n";
	}

	void print_content(node* v) const
	{
		if (!v)
			return;;
		print_content(v->left.get());
		std::cout << v->value << ' ';
		print_content(v->right.get());
	}

	bool tree_check(Node v) const noexcept
	{
		if (!v) return true;
		if (!tree_check(v->left) || !tree_check(v->right))
			return false;
		return (!v->left || v->left->value < v->value) &&
			   (!v->right || v->value < v->right->value);
	}

public:

	void print() const
	{
		std::cout << "tree_check : " << (tree_check(root->left) ? "GOOD" : "BAD") << '\n';
		std::cout << "set content: \n";
		std::cout << "value : #ROOT#\n";
		std::cout << "left : \n";
		print(root->left);
	}

	struct iterator
	{
		T const& operator*() const
		{
			return cur_node()->value;
		}

		iterator& operator++()
		{
			assert(!is_end());
			auto cur = cur_node();
			if (cur->right) {
				current_node = cur->right.get();
				go_left();
			} else {
				auto path = s->root->path_to_with_first(cur->value);
				auto v = path.back();
				path.pop_back();
				while (path.back()->left.get() != v)
					v = path.back(), path.pop_back();
				current_node = path.back();
			}
			return *this;
		}

		iterator operator++(int)
		{
			auto res = *this;
			++*this;
			return res;
		}

		iterator& operator--()
		{
			if (current_node->left) {
				current_node = current_node->left.get();
				go_right();
			} else {
				auto cur = cur_node();
				auto path = s->root->path_to(cur->value);
				auto v = path.back();
				path.pop_back();
				while (path.back()->right.get() != v)
					v = path.back(), path.pop_back();
				current_node = path.back();
			}
			return *this;
		}

		iterator operator--(int)
		{
			auto res = *this;
			--*this;
			return res;
		}

		iterator(iterator const& other) :
				s(other.s),
				current_node(other.current_node) {}

		void swap(iterator& other)
		{
			std::swap(s, other.s);
			std::swap(current_node, other.current_node);
		}

		iterator& operator=(iterator other)
		{
			auto tmp = other;
			swap(tmp);
			return *this;
		}

		operator bool() const noexcept
		{
			return !is_end();
		}

	private:

		persistent_set const* s;
		abstract_node const* current_node;

		iterator(const persistent_set* s, abstract_node const* current_node)
				: s(s),
				  current_node(current_node) {}

		explicit iterator(const persistent_set* s)
				: iterator(s, s->root.get()) {}

		bool is_end() const noexcept
		{
			return current_node->is_last();
		}

		node const* cur_node() const noexcept
		{
			return current_node->as_node();
		}

		void go_left() noexcept
		{
			while (current_node->left)
				current_node = current_node->left.get();
		}

		void go_right() noexcept
		{
			if (is_end())
				return;
			auto cur = cur_node();
			while (cur->right)
				cur = cur->right.get();
			current_node = cur;
		}

		// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
		// Сравнение с невалидным итератором не определено.
		// Сравнение итераторов двух разных контейнеров не определено.
		friend bool operator==(iterator it1, iterator it2)
		{
			return it1.current_node == it2.current_node;
		}

		friend bool operator!=(iterator it1, iterator it2)
		{
			return !(it1 == it2);
		}

		friend persistent_set;
	};

	persistent_set() noexcept
			: root(AbstractNode::make_shared(Node())) {}

	persistent_set(persistent_set const& other) noexcept
			: root(AbstractNode::make_shared(other.root->left)) {}

	persistent_set(persistent_set&& other) noexcept
			: root(std::move(other.root)) {}

	// Поиск элемента.
	// Возвращает итератор на найденный элемент, либо end(), если элемент
	// с указанным значением отсутвует.
	iterator find(T const& newVal)
	{
		if (!root->left)
			return end();
		auto cur = root->left.get();
		while (cur) {
			if (newVal < cur->value)
				cur = cur->left.get();
			else if (cur->value < newVal)
				cur = cur->right.get();
			else
				return iterator(this, cur);
		}
		return end();
	}

	// Вставка элемента.
	// 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
	//    на уже присутствующий элемент и false.
	// 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
	//    элемент и true.
	std::pair<iterator, bool> insert(T const& newValue)
	{
		auto found = find(newValue);
		if (found) {
			return { found, false };
		} else {
			auto path = root->path_to(newValue);
			auto v = Node::make_shared(std::move(newValue));
			found.current_node = v.get();
			for (size_t i = path.size(); i --> 0 ;) {
				if ((i != path.size() - 1 && path[i]->left.get() == path[i + 1]) ||
					(i == path.size() - 1 && newValue < path.back()->value)) {
					v = Node::make_shared(
							path[i]->value,
							v,
							path[i]->right
					);
				} else {
					v = Node::make_shared(
							path[i]->value,
							path[i]->left,
							v
					);
				}
			}
			root->left = v;
			return { found, true };
		}
	}

	void erase(iterator const& it)
	{
		assert(it);
		if (empty())
			return;
		auto value = *it;
		auto found = find(value);
		if (!found)
			return;
		auto path = root->path_to(value);
		path.pop_back();
		auto cur = merge(found.cur_node()->left, found.cur_node()->right);
		while (!path.empty()) {
			cur = value < path.back()->value ?
				  Node::make_shared(
						  path.back()->value,
						  cur,
						  path.back()->right
				  ) :
				  Node::make_shared(
						  path.back()->value,
						  path.back()->left,
						  cur
				  );
			path.pop_back();
		}
		root = AbstractNode::make_shared(cur);
	}

	bool empty() const noexcept { return !begin(); }

	iterator begin() const noexcept
	{
		auto beg = end();
		beg.go_left();
		return beg;
	}

	iterator end() const noexcept { return iterator(this); }

	~persistent_set() = default;

	persistent_set& operator=(persistent_set const& other) noexcept
	{
		persistent_set tmp(other);
		swap(tmp);
		return *this;
	}

	persistent_set& operator=(persistent_set&& other) noexcept
	{
		root = std::move(other.root);
		return *this;
	}

	void swap(persistent_set& other) noexcept
	{
		std::swap(root, other.root);
	}

};

#endif /* persistent_set_h */
