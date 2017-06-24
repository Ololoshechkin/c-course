//
//  binary_tree.h
//  Set
//
//  Created by Vadim on 24.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef binary_tree_h
#define binary_tree_h


#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <memory>

template <typename T>
class binary_tree
{
protected:
    struct node
    {
        T user_data;
        std::shared_ptr<node> parent;
        std::shared_ptr<node> left;
        std::shared_ptr<node> right;
        
        node(T const& user_data, std::shared_ptr<node> parent = std::shared_ptr<node>(nullptr), std::shared_ptr<node> left = std::shared_ptr<node>(nullptr),
             std::shared_ptr<node> right = std::shared_ptr<node>(nullptr))
        : user_data(user_data)
        , parent(parent)
        , left(left)
        , right(right)
        {}
        
        bool is_leaf() const
        {
            return !left && !right;
        }
        
        bool is_root() const
        {
            return parent == std::shared_ptr<node>(nullptr);
        }
        
        bool is_left_son() const
        {
            return is_root() ? false : parent->left.get() == this;
        }
        
        bool is_right_son() const
        {
            return is_root() ? false : parent->right.get() == this;
        }
        
    };
    
    std::shared_ptr<node> root;
    
    static std::shared_ptr<node> max_node(std::shared_ptr<node> x)
    {
        if (!x)
            return std::shared_ptr<node>(nullptr);
        std::shared_ptr<node> ans = x;
        while (ans->right.get())
        {
            ans = ans->right;
        }
        return ans;
    }
    
    static std::shared_ptr<node> min_node(std::shared_ptr<node> x)
    {
        if (!x)
            return std::shared_ptr<node>(nullptr);
        std::shared_ptr<node> ans = x;
        while (ans->left.get())
        {
            ans = ans->left;
        }
        return ans;
    }
    
    std::shared_ptr<node> insert(std::shared_ptr<node> current_node, std::shared_ptr<node> parent_node, std::shared_ptr<node> new_node)
    {
        if (!current_node.get())
        {
            new_node->parent = parent_node;
            return new_node;
        }
        if (new_node->user_data < current_node->user_data)
            current_node->left =  insert(current_node->left, current_node, new_node);
        else
            current_node->right = insert(current_node->right, current_node, new_node);
        return current_node;
    }
    
    std::shared_ptr<node> find_node(std::shared_ptr<node> current_node, T const& data)
    {
        if (!current_node.get())
            return std::shared_ptr<node>(nullptr);
        if (current_node->user_data == data)
            return current_node;
        if (data < current_node->user_data)
            return find_node(current_node->left, data);
        return find_node(current_node->right, data);
    }
    
    static const std::shared_ptr<T> get_data(std::shared_ptr<node> n)
    {
        return std::shared_ptr<T>(n? &n->user_data : nullptr);
    }
    
    void print(std::shared_ptr<node> cur) const
    {
        if (!cur.get())
            return;
        std::cout << "(";
        print(cur->left);
        std::cout << ") <- " << cur->user_data << "-> (";
        print(cur->right);
        std::cout << ")";
    }
    
public:
    
    virtual void insert(T const& new_data) = 0;
    
    virtual void erase(T const& old_data) = 0;
    
    virtual bool count(T const& data) = 0;
    
    virtual const T * next(T const& data) = 0;
    
    virtual const T * prev(T const& data) = 0;
    
    void print() const
    {
        print(root);
    }
    
};


#endif /* binary_tree_h */
