#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>
#include "list.hpp"
#include "test-counter.hpp"


template <typename T>
class List {
private:
    class Node {
    public:
        T item;
        List<T>::Node *next, *prev;
        Node() : next(NULL), prev(NULL) {}
        Node(T item) : item(item), next(NULL), prev(NULL) {}
        ~Node() {
            if (next != NULL)
                delete next;
        }
    };
    List<T>::Node *head, *last;
    size_t n;
public:
    List() {
        head = new List<T>::Node();
        last = new List<T>::Node();
        head->next = last;
        last->prev = head;
        n = 0;
    }
    List(const List<T> &rhs) {
        head = new List<T>::Node();
        last = new List<T>::Node();
        head->next = last;
        last->prev = head;
        n = 0;
        for (List<T>::Node *node = rhs.head->next; node != rhs.last; node = node->next)
            insert(node->item);
    }
    List& operator=(const List<T> &rhs) {
        delete head->next;
        last = new List<T>::Node();
        head->next = last;
        last->prev = head;
        n = 0;
        for (List<T>::Node *node = rhs.head->next; node != rhs.last; node = node->next)
            insert(node->item);
        return *this;
    }
    ~List() { delete head; }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    class Iterator {
        friend class List;
    private:
        List<T>::Node *node;
        Iterator(List<T>::Node *ptr) : node(ptr) {}
    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        reference operator*() const { return node->item; }
        Iterator& operator++() { if (node->next != NULL) node = node->next; return *this; }
        Iterator& operator--() { if (node->prev != NULL) node = node->prev; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.node == b.node; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.node != b.node; };  
    };

    Iterator begin() { return head->next; }
    Iterator end() { return last; }

    T top() {
        if (empty())
            throw std::logic_error("(List<T>::top) list is empty");
        return head->next->item;
    }

    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("(List<T>::lookup) index out of bounds");
        List<T>::Node *node;
        if (i < n - i) {
            node = head->next;
            while (i--)
                node = node->next;
        } else {
            node = last->prev;
            while (++i < n)
                node = node->prev;
        }
        return node->item;
    }

    
    void insert(T item) {
        List<T>::Node *inserted = new List<T>::Node(item);
        last->prev->next = inserted;
        inserted->prev = last->prev;
        last->prev = inserted;
        inserted->next = last;
        ++n;
    }

    void push(T item) { insert(0, item); }
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("(List<T>::insert) index out of bounds");
        List<T>::Node *inserted = new List<T>::Node(item);
        List<T>::Node *node;
        if (i < n - i) {
            node = head;
            while (i--)
                node = node->next;
            node->next->prev = inserted;
            inserted->next = node->next;
            node->next = inserted;
            inserted->prev = node;
        } else {
            node = last;
            while (i++ < n)
                node = node->prev;
            node->prev->next = inserted;
            inserted->prev = node->prev;
            node->prev = inserted;
            inserted->next = node;
        }
        ++n;
    }

    T pop() { return remove(0); }
    T remove(size_t i)  {
        if (i < 0 || i >= n)
            throw std::invalid_argument("(List<T>::remove) index out of bounds");
        if (n == 0)
            throw std::runtime_error("(List<T>::remove) list is empty");
        List<T>::Node *removed = NULL, *node;
        if (i < n - i) {
            node = head;
            while (i--)
                node = node->next;
            removed = node->next;
            node->next = removed->next;
            node->next->prev = node;
        } else {
            node = last;
            while (++i < n)
                node = node->prev;
            removed = node->prev;
            node->prev = removed->prev;
            node->prev->next = node;
        }
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    void remove_at(Iterator &it) {
        List<T>::Node *node = (--it).node;
        List<T>::Node *removed = node->next;
        node->next = removed->next;
        node->next->prev = node;
        removed->next = NULL;
        delete removed;
        --n;
        ++it;
    }

    bool remove_by(T &key) {
        List<T>::Node *node = head;
        while (++op && node->next != last && node->next->item != key)
            node = node->next;
        List<T>::Node *removed = node->next;
        if (removed == last)
            return false;
        node->next = removed->next;
        node->next->prev = node;
        removed->next = NULL;
        delete removed;
        --n;
        return true;
    }

    void concat_at(Iterator &it, List<T> &other) {
        List<T>::Node *node = (--it).node;
        List<T>::Node *tail = node->next;
        for (auto item : other) {
++op;       node->next = new List<T>::Node(item);
            node->next->prev = node;
            node = node->next;
        }
        node->next = tail;
        tail->prev = node;
        n += other.n;
        ++it;
    }

    friend std::ostream& operator<<(std::ostream& os, List<T>& list) {
        os << "[";
        for (auto it = list.begin(); it != list.end(); ++it)
            if (it == list.begin())
                os << *it;
            else
                os << "," << *it;
        os << "]";
        return os;
    }
};

#endif
