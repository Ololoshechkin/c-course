//
//  set.h
//  Set
//
//  Created by Vadim on 24.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef set_h
#define set_h

#include "splay_tree.h"
#include <exception>

template <typename T>
class set
{
private:
    splay_tree<T> t;
public:
    struct iterator
    {
        iterator& operator++()
        {
            if (value == nullptr)
                throw std::runtime_error("index out of bounds exception");
            value = std::shared_ptr<T>(tree.next(*value.get()));
            return *this;
        }
        iterator& operator++(int)
        {
            if (value == nullptr)
                throw std::runtime_error("index out of bounds exception");
            value = std::shared_ptr<T>(tree.next(*value.get()));
            return *this;
        }
        iterator& operator--()
        {
            if (value == nullptr)
                throw std::runtime_error("index out of bounds exception");
            value = std::shared_ptr<T>(tree.prev(*value.get()));
            return *this;
        }
        iterator& operator--(int)
        {
            if (value == nullptr)
                throw std::runtime_error("index out of bounds exception");
            value = std::shared_ptr<T>(tree.prev(*value.get()));
            return *this;
        }
        T const& operator*()
        {
            return *value.get();
        }
    private:
        std::shared_ptr<splay_tree<T>> tree;
        std::shared_ptr<T> value;
        iterator(std::shared_ptr<T> tree, std::shared_ptr<T> value)
        : tree(tree)
        , value(value)
        {}
    };
    iterator begin()
    {
        return iterator(std::shared_ptr<splay_tree<T>>(&t),
                        t.min_value());
    }
    iterator end()
    {
        return iterator(std::shared_ptr<splay_tree<T>>(&t),
                        std::shared_ptr<T> (nullptr));
    }
};


#endif /* set_h */
