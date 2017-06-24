//
//  rotatable_tree.h
//  Set
//
//  Created by Vadim on 24.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef rotatable_tree_h
#define rotatable_tree_h

#include "binary_tree.h"

template <typename T>
class rotatable_tree : public binary_tree<T>
{
    
protected:
    using node = typename binary_tree<T>::node;
    void rotate_right(std::shared_ptr<node> x)
    {
        if (x->is_root())
            return;
        std::shared_ptr<node> p = x->parent;
        x->parent = p->parent;
        if (x->parent)
        {
            if (p->is_left_son())
                x->parent->left = x;
            else
                x->parent->right = x;
        }
        std::shared_ptr<node> x_r = x->right;
        x->right = p, p->parent = x;
        p->left = x_r;
        if (x_r)
            x_r->parent = p;
    }
    
    void rotate_left(std::shared_ptr<node> x)
    {
        if (x->is_root())
            return;
        std::shared_ptr<node> p = x->parent;
        x->parent = p->parent;
        if (x->parent)
        {
            if (p->is_left_son())
                x->parent->left = x;
            else
                x->parent->right = x;
        }
        std::shared_ptr<node> x_l = x->left;
        x->left = p, p->parent = x;
        p->right = x_l;
        if (x_l)
            x_l->parent = p;
    }
    
};


#endif /* rotatable_tree_h */
