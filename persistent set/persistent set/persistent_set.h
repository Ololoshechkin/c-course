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

template <typename T, template <typename> class smart_ptr = shared_ptr>
class persistent_set {
private:
    struct base_node {
        smart_ptr<base_node> left, right;
        virtual bool operator<(base_node& other) {
            return false;
        }
    };
    struct node: public base_node {
        T value;
        bool operator<(base_node& other) {
            return true;
        }
        bool operator<(node& other) {
            return value < other.value;
        }
        node next() {
            
        }
    };
    smart_ptr<node> root;
public:
    // Bidirectional iterator.
    struct iterator
    {
        T const& operator*() const {
            return *path.back();
        }
        iterator& operator++() {
            while(!*cur_node()->right) {
                if (path.empty()) throw "FuckingShitException";
                path.pop_back();
            }
            path.push_back(cur_node()->right);
            return this;
        }
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
    private:
        std::vector<smart_ptr<node>> path;
        node* cur_node() {
            return *path.back();
        }
    };
    // Создает пустой persistent_set.
    persistent_set();
    // Создает копию указанного persistent_set-а.
    persistent_set(persistent_set const&);
    // Изменяет this так, чтобы он содержал те же элементы, что и rhs.
    // Инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    persistent_set& operator=(persistent_set const& rhs);
    // Деструктор. Вызывается при удалении объектов persistent_set.
    // Инвалидирует все итераторы ссылающиеся на элементы этого persistent_set
    // (включая итераторы ссылающиеся на элемент следующий за последним).
    ~persistent_set();
    // Поиск элемента.
    // Возвращает итератор на найденный элемент, либо end(), если элемент
    // с указанным значением отсутвует.
    iterator find(T);
    // Вставка элемента.
    // 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
    //    на уже присутствующий элемент и false.
    // 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
    //    элемент и true.
    // Если вставка произведена, инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    std::pair<iterator, bool> insert(T);
    // Удаление элемента.
    // Инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    void erase(iterator);
    // Возващает итератор на элемент с минимальный ключом.
    iterator begin() const;
    // Возващает итератор на элемент следующий за элементом с максимальным ключом.
    iterator end() const;
};

// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
// Сравнение с невалидным итератором не определено.
// Сравнение итераторов двух разных контейнеров не определено.
template <typename T>
bool operator==(typename persistent_set<T>::iterator, typename persistent_set<T>::iterator);
template <typename T>
bool operator!=(typename persistent_set<T>::iterator, typename persistent_set<T>::iterator);



#endif /* persistent_set_h */
