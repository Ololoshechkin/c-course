//
//  persistent_set.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef persistent_set_h
#define persistent_set_h

#include "shared_ptr.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <iostream>
#define Node smart_ptr<node>

template <typename T, template <typename> class smart_ptr = shared_ptr>
class persistent_set {
private:
    struct node {
        T value;
        Node left, right;
        bool operator == (node other) const noexcept {
            return left == other.left && right == other.right;
        }
        node(T value, Node left = Node(), Node right = Node())
        : value(value), left(left), right(right)
        {}
        Node the_least_child() const noexcept {
            return left ? left->the_least_child() : right->the_least_child();
        }
    };
    Node root;
    Node copy(Node other) const {
        return Node::of(other->value, other->left, other->right);
    }
    // inv : l.value <= r.value
    Node merge(Node l, Node r) const {
        if (!l) return r;
        if (!r) return l;
        if (rand() & 1) {
            return merge(l->right, r);
        } else {
            return merge(l, r->left);
        }
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
            if (is_end()) {
                path.push_back(root());
                go_right();
            } else {
                if (cur_node()->left) {
                    path.push_back(cur_node()->left);
                    go_right();
                } else {
                    while(true) {
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
        bool operator==(iterator const& other) const  {
            return root() == other.root() && path.empty() == other.path.empty() &&
            ((path.empty() && other.path.empty()) || cur_node() == other.cur_node());
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
    // Поиск элемента.
    // Возвращает итератор на найденный элемент, либо end(), если элемент
    // с указанным значением отсутвует.
    iterator find(T newVal) {
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
        Node last = it.path.back();
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
    
    iterator begin() const {
        if (root) {
            auto st = iterator(this, { root });
            st.go_left();
            return st;
        }
        return iterator(this, {});
    }
    iterator end() const {
        return iterator(this, {});
    }
    iterator last() const {
        iterator en = end();
        return --en;
    }
};

// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
// Сравнение с невалидным итератором не определено.
// Сравнение итераторов двух разных контейнеров не определено.
template <typename T>
bool operator==(typename persistent_set<T>::iterator it1, typename persistent_set<T>::iterator it2) {
    return it1.path == it2.path && it1.root.get() == it2.root.get();
}

template <typename T>
bool operator!=(typename persistent_set<T>::iterator it1, typename persistent_set<T>::iterator it2) {
    return !(it1 == it2);
}



#endif /* persistent_set_h */
