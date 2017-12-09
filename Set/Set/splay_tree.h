//
//  splay_tree.h
//  Set
//
//  Created by Vadim on 24.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef splay_tree_h
#define splay_tree_h

#include "rotatable_tree.h"

template <typename T>
class splay_tree : public rotatable_tree<T>
{
private:
    using binary_tree<T>::root;
    using node = typename binary_tree<T>::node;
    using rotatable_tree<T>::rotate_right;
    using rotatable_tree<T>::rotate_left;
    using binary_tree<T>::min_node;
    using binary_tree<T>::max_node;
    using binary_tree<T>::insert;
    using binary_tree<T>::find_node;
    bool zig(std::shared_ptr<node> x)
    {
        std::shared_ptr<node> p = x->parent;
        if (!p->is_root())
            return false;
        if (x->is_left_son())
            rotate_right(x);
        else
            rotate_left(x);
        return true;
    }
    
    bool zig_zig(std::shared_ptr<node> x)
    {
        if (x->is_root())
            return false;
        std::shared_ptr<node> p = x->parent;
        if (p->is_root() || (x->is_left_son() != p->is_left_son()))
            return false;
        if (x->is_left_son())
        {
            rotate_right(p);
            rotate_right(x);
        }
        else
        {
            rotate_left(p);
            rotate_left(x);
        }
        return true;
    }
    
    bool zig_zag(std::shared_ptr<node> x)
    {
        if (x->is_root())
            return false;
        std::shared_ptr<node> p = x->parent;
        if (p->is_root() || (x->is_left_son() == p->is_left_son()))
            return false;
        if (x->is_left_son()) {
            rotate_right(x);
            rotate_left(x);
        }
        else
        {
            rotate_left(x);
            rotate_right(x);
        }
        return true;
    }
    
    void splay(std::shared_ptr<node> x)
    {
        if (!x.get())
        {
            root = std::shared_ptr<node>(nullptr);
            return;
        }
        while (!x->is_root())
        {
            if (zig(x))
                break;
            if(zig_zig(x))
                continue;
            if(zig_zag(x))
                continue;
        }
        root = x;
    }
    
    std::shared_ptr<node> merge(std::shared_ptr<node> left, std::shared_ptr<node> right)
    {
        left = max_node(left);
        splay(left);
        if (left)
        {
            left->right = right;
            if (right)
                right->parent = left;
        }
        else
        {
            left = right;
            if (left)
                left->parent = std::shared_ptr<node>(nullptr);
        }
        return left;
    }
    
    void splay(T const& data)
    {
        std::shared_ptr<node> answer = find_node(root, data);
        if (answer)
            splay(answer);
    }
    
public:
    splay_tree()
    {
        root = std::shared_ptr<node>(nullptr);
    }
    
    void insert(T const& new_data) override
    {
        if (count(new_data))
            return;
        node* new_n = new node(new_data);
        std::shared_ptr<node> new_node(new_n);
        root = insert(root, std::shared_ptr<node>(nullptr), new_node);
        splay(new_node);
    }
    
    void erase(T const& old_data) override
    {
        if (!count(old_data))
            return;
        if (root->left)
            root->left->parent = std::shared_ptr<node>(nullptr);
        if (root->right)
            root->right->parent = std::shared_ptr<node>(nullptr);
        root = merge(root->left, root->right);
        if (root)
            root->parent = std::shared_ptr<node>(nullptr);
    }
    
    bool count(T const& data) override
    {
        splay(data);
        return root && root->user_data == data;
    }
    
    std::shared_ptr<node> next(T const& data) override
    {
        bool should_erase = false;
        if (!count(data)) {
            insert(data);
            should_erase = true;
        }
        std::shared_ptr<node> answer = min_node(root->right);
        if (should_erase)
            erase(data);
        return answer;
    }
    
    std::shared_ptr<node> prev(T const& data) override
    {
        bool should_erase = false;
        if (!count(data))
            insert(data), should_erase = true;
        std::shared_ptr<node> answer = max_node(root->left);
        if (should_erase)
            erase(data);
        return answer;
    }
    
    const std::shared_ptr<T> min_value()
    {
        return binary_tree<T>::get_data(min_node(root));
    }
    
    const std::shared_ptr<T> max_value()
    {
        return binary_tree<T>::get_data(max_node(root));
    }
    
    using binary_tree<T>::print;
    
};


#endif /* splay_tree_h */
