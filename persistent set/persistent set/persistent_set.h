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
#define val auto
#define List std::vector
#define add push_back
#define Node smart_ptr<node>
#define a.last() a[a.size() - 1]

template <typename T>
List<T> reversedListOf(T last, T args...) {
    val res = reversedListOf(args);
    res.add(last);
    return res;
}

template <typename T>

List<T> reversedListOf() {
    return List<T>();
}

template <typename T>
List<T> listOf(T args...) {
    val rev = reversedListOf(args);
    std::reverse(rev.begin(), rev.end());
    return rev;
}

template <typename T, template <typename> class smart_ptr = shared_ptr>
class persistent_set {
private:
    struct node {
        T value;
        Node left, right;
        bool operator == (node other) const noexcept {
            return left.get() == other.left.get() &&
            right.get() == other.right.get();
        }
        friend bool operator == (Node left, Node right) noexcept {
            return left.get() == right.get();
        }
        node(T value, Node left = Node(), Node right = Node())
        : value(value), left(left), right(right)
        {}
    };
    Node root;
    Node copy(Node other) {
        return Node::of(other->value, other->left, other->right);
    }
public:
    // Bidirectional iterator.
    struct iterator {
        T const& operator*() const {
            return *path.back();
        }
        iterator& operator++() {
            assert(!path.empty());
            Node last_node(nullptr);
            while(true) {
                if (path.empty()) break;
                val cur = cur_node(), right = cur->right();
                if (!right || right == last_node) break;
                last_node = cur;
                path.pop_back();
            }
            if (cur_node()->right)
                path.push_back(cur_node()->right);
            go_left();
            return this;
        }
        iterator operator++(int) {
            val ans = *this;
            ++*this;
            return ans;
        }
        iterator& operator--() {
            if (is_end()) {
                path.push_back(root);
                go_right();
            } else {
                Node last_node(nullptr);
                while(true) {
                    assert(!path.empty());
                    val cur = cur_node(), left = cur->left();
                    if (!left || left == last_node) break;
                    last_node = cur;
                    path.pop_back();
                }
                if (cur_node()->left)
                    path.push_back(cur_node()->left);
                go_right();
                return this;
            }
        }
        iterator operator--(int) {
            val ans = *this;
            --*this;
            return ans;
        }
        bool operator==(iterator const& other) {
            return root == other.root &&
            path.empty() == other.path.empty() &&
            ((path.empty() && other.path.empty())
             || cur_node() == other.cur_node());
        }
    private:
        List<Node> path;
        Node root;
        iterator(List<Node> path, Node root)
        : path(path), root(root)
        {}
        bool is_end() const noexcept {
            return path.empty();
        }
        Node cur_node() const noexcept {
            return *path.back();
        }
        void go_left() {
            val cur = cur_node();
            while (cur->left) {
                cur = cur->left;
                path.push_back(cur);
            }
        }
        void go_right() {
            val cur = cur_node();
            while (cur->right) {
                cur = cur->right;
                path.push_back(cur);
            }
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
        val cur = root;
        val path = listOf(root);
        while (true) {
            val should_break = false;
            if (cur->value < newVal) {
                if (!cur->right) return end();
                else cur = cur->right;
            } else if (newVal < cur->value){
                if (!cur->left) return end();
                else cur = cur->left;
            } else should_break = true;
            path.add(cur);
            if (should_break) break;
        }
        return iterator(path, root);
    }
    // Вставка элемента.
    // 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
    //    на уже присутствующий элемент и false.
    // 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
    //    элемент и true.
    // Если вставка произведена, инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    std::pair<iterator, bool> insert(T newValue) {
        val found = find(newValue);
        if (found == end()) {
            return { found, false };
        } else {
            val newRoot = copy(root);
            val cur = newRoot, cur_old = root;
            val path = listOf(newRoot);
            while (true) {
                if (!cur_old) break;
                val should_break = false;
                if (cur_old->value < newValue) {
                    cur_old = cur_old->right;
                    if (cur_old) cur->right = copy(cur_old);
                    else cur->right = Node(newValue), should_break = 1;
                } else if (newValue < cur->value) {
                    cur_old = cur_old->left;
                    if (cur_old) cur->left = copy(cur_old);
                    else cur->left = Node(newValue), should_break = 1;
                }
                path.add(cur);
                if (should_break) break;
            }
            return { iterator(path, newRoot), true };
        }
    }
    
    void erase(iterator it) {
        
    }
    
    iterator begin() const {
        val st = iterator(root, listOf<Node>());
        st.go_left();
    }
    iterator end() const {
        return iterator(root, listOf<Node>());
    }
};

// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
// Сравнение с невалидным итератором не определено.
// Сравнение итераторов двух разных контейнеров не определено.
template <typename T>
bool operator==(typename persistent_set<T>::iterator, typename persistent_set<T>::iterator);
template <typename T>
bool operator!=(typename persistent_set<T>::iterator, typename persistent_set<T>::iterator);



#endif /* persistent_set_h */
