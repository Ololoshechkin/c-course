//
//  set.h
//  set_no_balance
//
//  Created by Vadim on 24.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef set_h
#define set_h

#include <iostream>
#include <algorithm>
#include <memory>
#include <exception>

template <typename T>
class set {
private:
    struct node
    {
        T user_data;
        node* left;
        node* right;
        node* parent;
        
        node(T const& user_data,
             node* left = nullptr,
             node* right = nullptr,
             node* parent = nullptr)
        : user_data(user_data)
        , left(left)
        , right(right)
        , parent(parent)
        {}
        
        bool is_leaf() const
        {
            return !left && !right;
        }
        
        bool is_root() const
        {
            return parent == nullptr;
        }
        
        bool is_left_son() const
        {
            return is_root() ? false : parent->left == this;
        }
        
        bool is_right_son() const
        {
            return is_root() ? false : parent->right == this;
        }
        
        node* next(bool should_skip_right = 0) const
        {
            if (!right || should_skip_right)
            {
                if (!parent) return nullptr;
                if (is_right_son())
                    return parent->next(1);
                return parent->right ? parent->next(0) : parent;
            }
            else
            {
                return min_node(right);
            }
        }
        
        node* prev(bool should_skip_left = 0) const
        {
            if (!left || should_skip_left)
            {
                if (!parent) return nullptr;
                if (is_left_son())
                    return parent->prev(1);
                return parent->left ? parent->prev(0) : parent;
            }
            else
            {
                return max_node(left);
            }
        }
        
        void node_dfs_delete()
        {
            if (left) {
                left->node_dfs_delete();
                delete left;
            }
            if (right)
            {
                right->node_dfs_delete();
                delete right;
            }
        }
        
        ~node()
        {
            delete left;
            delete right;
        }
        
    };
    
    node* root;
    size_t sz = 0;
    
    static node* max_node(node* x)
    {
        if (!x)
            return nullptr;
        node* ans = x;
        while (ans->right)
        {
            ans = ans->right;
        }
        return ans;
    }
    
    static node* min_node(node* x)
    {
        if (!x)
            return nullptr;
        node* ans = x;
        while (ans->left)
        {
            ans = ans->left;
        }
        return ans;
    }
    
    T* get_data(node* n)
    {
        return n? &n->user_data : nullptr;
    }
    
    set(node* const& root, size_t sz)
    : root(root)
    , sz(sz)
    {}
    
    node* build_copy(node* const& cur_node)
    {
        if (!cur_node) return nullptr;
        node* left_son = build_copy(cur_node->left);
        node* right_son;
        node* copy_node;
        try {
            right_son = build_copy(cur_node->right);
        } catch(...)
        {
            delete left_son;
            throw;
        }
        try {
            copy_node = new node();
        } catch(...) {
            delete left_son;
            delete right_son;
            throw;
        }
        copy_node->left = left_son;
        copy_node->right = right_son;
        copy_node->left->parent = copy_node;
        copy_node->right->parent = copy_node;
        return copy_node;
    }
    
    void clear(node*& cur_node)
    {
        if (!cur_node) return;
        clear(cur_node->left);
        clear(cur_node->right);
        cur_node.~node();
    }
    
    node* lower_bound(node* cur_node, T const& value) const
    {
        if (!cur_node || cur_node->user_data == value)
            return cur_node;
        if (cur_node->user_data < value)
            return lower_bound(cur_node->right, value);
        node* answer = lower_bound(cur_node->left, value);
        if (answer && answer->user_data >= value)
            return answer;
        return cur_node;
    }
    
    void print(node* cur_node)
    {
        if (!cur_node)
            return;
        if (cur_node->left && cur_node->left->parent != cur_node)
        {
            std::cout << " FAIL PARENT(of l) IN : " << cur_node->user_data << '\n';
        }
        if (cur_node->right && cur_node->right->parent != cur_node)
        {
            std::cout << " FAIL PARENT(of r) IN : " << cur_node->user_data << '\n';
            std::cout << " Actual parent (of" << cur_node->right->user_data << " is : " << cur_node->right->parent->user_data << '\n';
        }
        std::cout << "(";
        print(cur_node->left);
        std::cout << " <- " << cur_node->user_data << " -> ";
        print(cur_node->right);
        std::cout << ")";
    }
    
    void definite_delete(node* n)
    {
        if (n->parent->left == n)
            n->parent->left = nullptr;
        if (n->parent->right== n)
            n->parent->right = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        delete n;
    }
   
public:
    
    set()
    : set(nullptr, 0)
    {}
    
    void swap(set& other)
    {
        std::swap(root, other.root);
        std::swap(sz, other.sz);
    }
    
    set(set const& other)
    : set(other.build_copy(other.root), other.sz)
    {}
    
    set& operator=(set const& other)
    {
        set tmp(other);
        swap(tmp);
        return *this;
    }
    
    bool empty() const
    {
        return !sz;
    }
    
    size_t size()
    {
        return sz;
    }
    
    void clear()
    {
        clear(root);
    }
    
    struct iterator
    {
        iterator()
        : n(nullptr)
        , s(nullptr)
        {}
        iterator& operator++()
        {
            if (!n)
                throw std::runtime_error("operator++ from end-iterator is depricated");
            n = n->next();
            return *this;
        }
        iterator& operator--()
        {
            if (!n)
            {
                n = max_node(s->root);
                return *this;
            }
            n = n->prev();
            if (!n)
                throw std::runtime_error("operator-- from begin-iterator is depricated");
            return *this;
        }
        iterator& operator++(int)
        {
            iterator& answer = *this;
            operator++();
            return answer;
        }
        iterator& operator--(int)
        {
            iterator& answer = *this;
            --*this;
            return answer;
        }
        T const& operator*() const
        {
            return n->user_data;
        }
        bool operator==(iterator const& other) const
        {
            if (!n)
                return !other.n;
            if (!other.n)
                return 0;
            return n->user_data == other.n->user_data;
        }
        bool operator!=(iterator const& other) const
        {
            return !(operator==(other));
        }
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T const* pointer;
        typedef T const& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        friend set;
        node* n;
        const set* s;
        iterator(node* n, const set* s)
        : n(n)
        , s(s)
        {}
        
    };
    
    typedef iterator const_iterator;
    
    const_iterator end() const
    {
        return iterator(nullptr, this);
    }
    
    const_iterator begin() const
    {
        if (!root)
            return end();
        return iterator(min_node(root), this);
    }
    
    iterator insert(T const& value)
    {
        ++sz;
        if (!root)
        {
            root = new node(value);
            return begin();
        }
        else
        {
            node* cur_node = root;
            while (1)
            {
                if (cur_node->user_data == value)
                {
                    return iterator(cur_node, this);
                }
                if (cur_node->user_data < value)
                {
                    if (!cur_node->right)
                        cur_node->right = new node(
                                value,
                                nullptr,
                                nullptr,
                                cur_node
                     );
                    cur_node = cur_node->right;
                }
                else
                {
                    if (!cur_node->left)
                        cur_node->left = new node(
                                value,
                                nullptr,
                                nullptr,
                                cur_node
                    );
                    cur_node = cur_node->left;
                }
            }
        }
        __builtin_unreachable();
    }
    
    const_iterator lower_bound(T const& value) const
    {
        if (!root) return end();
        node* ans_node = lower_bound(root, value);
        if (!ans_node)
            return end();
        return iterator(ans_node, this);
    }
    
    const_iterator find(T const& value) const
    {
        iterator answer = lower_bound(value);
        if (answer != end() && answer.n->user_data == value)
            return answer;
        return end();
    }
    
    const_iterator upper_bound(T const& value) const
    {
        if (!root) return end();
        iterator answer = find(value);
        if (answer != end()) return ++answer;
        return lower_bound(value);
    }
    
    iterator erase(T const& value)
    {
        if (!root) return end();
        iterator found = find(value);
        if (found == end())
            return found;
        node* exact = found.n;
        bool was_left_son = exact->is_left_son();
        bool was_root = exact->is_root();
        if (!exact->left)
        {
            if (was_root)
                root = exact->right;
            else {
                if (was_left_son)
                    exact->parent->left = exact->right;
                else
                    exact->parent->right = exact->right;
            }
            if (exact->right)
                exact->right->parent = exact->parent;
            definite_delete(exact);
        }
        else if (!exact->right)
        {
            if (was_root)
                root = exact->left;
            else {
                if (was_left_son)
                    exact->parent->left = exact->left;
                else
                    exact->parent->right = exact->left;
            }
            if (exact->left)
                exact->left->parent = exact->parent;
            definite_delete(exact);
        }
        else
        {
            node* r_min = min_node(exact->right);
            exact->user_data = r_min->user_data;
            definite_delete(r_min);
        }
        return lower_bound(value);
    }
    
    typedef std::reverse_iterator<iterator> reverse_iterator;
    
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    
    void print()
    {
        print(root);
    }
    
    ~set()
    {
        delete root;
    }
    
};

#endif /* set_h */
