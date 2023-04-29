#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>
#include "list.hpp"


template <typename T>
class ListNode {
public:
    T item;
    ListNode<T> *next, *prev;
    ListNode() : next(NULL), prev(NULL) {}
    ListNode(T item) : item(item), next(NULL), prev(NULL) {}
    ~ListNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class List {
private:
    ListNode<T> *head, *last;
    size_t n;
public:
    List() {
        head = new ListNode<T>();
        last = new ListNode<T>();
        head->next = last;
        last->prev = head;
        n = 0;
    }
    List(const List<T> &rhs) {
        head = new ListNode<T>();
        last = new ListNode<T>();
        head->next = last;
        last->prev = head;
        n = 0;
        for (ListNode<T> *node = rhs.head->next; node != rhs.last; node = node->next)
            insert(node->item);
    }
    List& operator=(const List<T> &rhs) {
        delete head->next;
        last = new ListNode<T>();
        head->next = last;
        last->prev = head;
        n = 0;
        for (ListNode<T> *node = rhs.head->next; node != rhs.last; node = node->next)
            insert(node->item);
        return *this;
    }
    ~List() { delete head; }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    struct Iterator {
        friend class List;
    private:
        ListNode<T> *node;
    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(ListNode<T> *ptr) : node(ptr) {}
        reference operator*() const { return node->item; }
        Iterator& operator++() { node = node == NULL ? NULL : node->next; return *this; }
        Iterator& operator--() { node = node == NULL ? NULL : node->prev; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.node == b.node; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.node != b.node; };  
    };

    Iterator begin() { return head->next; }
    Iterator end() { return last; }

    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        ListNode<T> *node;
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

    void push(T item) { insert(0, item); }
    void insert(T item) { insert(n, item); }
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        ListNode<T> *inserted = new ListNode<T>(item);
        ListNode<T> *node;
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
            throw std::invalid_argument("index out of bounds");
        if (n == 0)
            throw std::runtime_error("list is empty");
        ListNode<T> *removed = NULL, *node;
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
        ListNode<T> *node = (--it).node;
        ListNode<T> *removed = node->next;
        node->next = removed->next;
        node->next->prev = node;
        removed->next = NULL;
        delete removed;
        --n;
    }

    bool remove_by(T &key) {
        ListNode<T> *node = head;
        while (node->next != last && node->next->item != key)
            node = node->next;
        ListNode<T> *removed = node->next;
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
        ListNode<T> *node = (--it).node;
        ListNode<T> *tail = node->next;
        for (auto item : other) {
            node->next = new ListNode<T>(item);
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
        for (ListNode<T> *current = list.head->next; current != list.last; current = current->next)
            if (current == list.head->next)
                os << current->item;
            else
                os << "," << current->item;
        os << "]";
        return os;
    }
};

#endif
