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

template <typename T, template <typename> class smart_ptr = std::shared_ptr>//my_linked_ptr>//my_shared_ptr>//std::shared_ptr>
class persistent_set
{
private:

	struct abstract_node;
	struct node;

	struct abstract_node
	{
		typedef smart_ptr<abstract_node> AbstractNode;
		typedef smart_ptr<node> Node;
		Node left;

		abstract_node(abstract_node const &other) noexcept
				: left(other.left)
		{}

		abstract_node(abstract_node &&other) noexcept
				: left(std::move(other.left))
		{}

		explicit abstract_node(Node left) noexcept
				: left(std::move(left))
		{}

		virtual bool operator==(abstract_node const &other) const noexcept
		{
			return left == other.left;
		}

		virtual bool operator==(node const &other) const noexcept
		{
			return false;
		}

		virtual bool operator<(node const &other) const noexcept
		{
			return false;
		}

		virtual bool operator<(T const& value) const noexcept
		{
			return false;
		}

		friend bool operator<(T const& value, abstract_node const& self) noexcept
		{
			return true;
		}

		virtual bool is_last()
		{
			return true;
		}

		node* as_node()
		{
			return static_cast<node*>(this);
		}

	};

	struct node : public abstract_node
	{
		using Node = typename abstract_node::Node;
		T value;
		Node right;

		bool operator==(node const& other) const noexcept
		{
			return this->left == other.left && right == other.right && value == other.value;
		}

		bool operator==(abstract_node const &other) const noexcept
		{
			return false;
		}

		bool operator<(abstract_node const &other) const noexcept
		{
			return true;
		}

		bool operator<(node const &other) const noexcept
		{
			return value < other.value;
		}

		bool operator<(T const& value) const noexcept
		{
			return this->value < value;
		}

		friend bool operator<(T const& value, node const& self) noexcept
		{
			return value < self.value;
		}

		explicit node(T const &value, Node left = Node(), Node right = Node()) noexcept(noexcept(T(value)))
				: abstract_node(std::move(left)),
				  right(std::move(right)),
				  value(value)
		{}

		T get_min()
		{
			return this->left ? this->left->get_min() : value;
		};

		Node copy_path()
		{
			return this->left ? Node::make_shared(value, this->left->copy_path(), right) : right;
		};

		bool is_last()
		{
			return false;
		}

	};

	using AbstractNode = typename abstract_node::AbstractNode;
	using Node = typename abstract_node::Node;
	typedef std::vector<abstract_node*> path_t;

	abstract_node* root;

	void print(Node v)
	{
		if (!v) return;
		print(v->left);
		std::cout << " " << v->value << " ";
		print(v->right);
	}

public:

	void print()
	{
		print(root);
		std::cout << '\n';
	}

	// Bidirectional iterator.
	struct iterator
	{

		T const &operator*() const
		{
			return cur_node()->value;
		}

		iterator &operator++()
		{
			auto cur = cur_node();
			if (cur->right) {
				cur = cur->right.get();
				go_left();
			} else {
				auto path = path_to(cur);
				auto v = path.back()->as_node();
				path.pop_back();
				while (path.back()->left.get() != v)
					v = path.back(), path.pop_back();
				cur = path.back()->as_node();
			}
			current_node = cur;
			return *this;
		}

		iterator operator++(int)
		{
			auto res = *this;
			++*this;
			return res;
		}

		iterator &operator--()
		{
			auto cur = cur_node();
			if (cur->left) {
				cur = cur->left.get();
				go_right();
			} else {
				auto path = path_to(cur);
				auto v = path.back()->as_node();
				path.pop_back();
				while (path.back()->as_node()->right.get() != v)
					v = path.back(), path.pop_back();
				cur = path.back()->as_node();
			}
			current_node = cur;
			return *this;
		}

		iterator operator--(int)
		{
			auto res = *this;
			--*this;
			return res;
		}

		iterator(iterator const &other) :
				s(other.s),
				current_node(other.current_node)
		{}

		void swap(iterator &other)
		{
			std::swap(s, other.s);
			std::swap(current_node, other.current_node);
		}

		iterator &operator=(iterator other)
		{
			auto tmp = other;
			swap(tmp);
			return *this;
		}

		bool operator==(iterator const &other) const
		{
			return s == other.s && current_node == other.current_node;
		}

		bool operator!=(iterator const &other) const noexcept
		{
			return !(*this == other);
		}

	private:

		const persistent_set* s;
		abstract_node* current_node;

		node* root() const
		{
			return s->root->as_node();
		}

		iterator(const persistent_set* s, abstract_node* cur_node)
				: s(s),
				  current_node(current_node)
		{}

		explicit iterator(const persistent_set* s)
				: iterator(s, s->root)
		{}

		bool is_end() const noexcept
		{
			return current_node->is_last();
		}

		node* cur_node() const noexcept
		{
			return current_node->as_node();
		}

		node* cur_node_or_null() const noexcept
		{
			return is_end() ? nullptr : cur_node();
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

		path_t path_to(node* cur) {
			path_t path;
			path.push_back(s->root);
			auto v = s->root->left;
			while (true) {
				path.push_back(v);
				if (v < cur) {
					v = v->right.get();
				} else if (cur < v) {
					v = v->left.get();
				} else {
					break;
				}
			}
			return path;
		}

		friend persistent_set;
	};

	persistent_set()
			: root(nullptr)
	{}

	persistent_set(persistent_set const &other)
			: root(other.root)
	{}

	void swap(persistent_set &other)
	{
		std::swap(root, other.root);
	}

	persistent_set &operator=(persistent_set const &rhs)
	{
		persistent_set tmp(rhs);
		swap(tmp);
		return *this;
	}

	iterator end() const
	{
		return iterator(this);
	}

	iterator begin() const
	{
		auto beg = end();
		beg.go_left();
		return beg;
	}

	iterator last() const
	{
		iterator en = end();
		return --en;
	}

	// Поиск элемента.
	// Возвращает итератор на найденный элемент, либо end(), если элемент
	// с указанным значением отсутвует.
	iterator find(T const &newVal)
	{
		if (root->is_last())
			return end();
		auto cur = root->as_node();
		while (cur) {
			if (newVal < cur->value)
				cur = cur->left;
			else if (cur->value < newVal)
				cur = cur->right;
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
	std::pair<iterator, bool> insert(T newValue)
	{
		if (!root) {
			root = new node(newValue);
			return { iterator(this, root), true };
		}
		auto found = find(newValue);
		if (found != end()) {
			return { found, false };
		} else {
			iterator iter(this);
			path_t path;
			auto v = root;
			while (v) {
				if (newValue < *v) {
					if (!v->left) {
						iter.current_node = new node(std::move(newValue));
						path.push_back(iter.current_node);
						break;
					}
					v = v->left.get();
				} else if (*v < newValue) {
					if (!v->as_node()->right) {
						iter.current_node = new node(std::move(newValue));
						path.push_back(iter.current_node);
						break;
					}
					v = v->as_node()->right.get();
				} else
					return { iter, false };
			}
			size_t i = path.size() - 1;
			while (i > 0) {
				--i;
				auto cur_v = path[i];
				if (newValue < *cur_v)
					path[i] = new node(cur_v->as_node()->value, Node(path[i + 1]->as_node()), cur_v->as_node()->right);
				else
					path[i] = new node(cur_v->as_node()->value, cur_v->left, Node(path[i + 1]->as_node()));
			}
			root = path.front();
			return { iter, true };
		}
	}

	void erase(iterator it)
	{
		assert(!it.is_end());
		auto last = Node(it.cur_node());
		Node cur_v = !last->left ? last->right :
					 !last->right ? last->left : Node::make_shared(
							 last->right->get_min(),
							 last->left,
							 last->right->copy_path()
					 );
		auto path = it.path_to(it.cur_node());
		for (auto i = path.size() - 1; i > 0;) {
			Node parent = Node(path[--i]);
			if (parent->left == last)
				cur_v = Node::make_shared(parent->value, cur_v, parent->right);
			else
				cur_v = Node::make_shared(parent->value, parent->left, cur_v);
			last = parent;
		}
		root = cur_v;
	}

	~persistent_set() = default;

};

// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
// Сравнение с невалидным итератором не определено.
// Сравнение итераторов двух разных контейнеров не определено.
template <typename T>
bool operator==(typename persistent_set<T>::iterator it1, typename persistent_set<T>::iterator it2)
{
	return it1.s == it2.s && it1.root == it2.root;
}

template <typename T>
bool operator!=(typename persistent_set<T>::iterator it1, typename persistent_set<T>::iterator it2)
{
	return !(it1 == it2);
}


#endif /* persistent_set_h */
