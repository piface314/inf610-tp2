#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>
#include "list.hpp"


template <typename T>
class ListNode {
public:
    T item;
    ListNode<T> *next;
    ListNode() : next(NULL) {}
    ListNode(T item) : item(item), next(NULL) {}
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
        this->head = this->last = new ListNode<T>();
        this->n = 0;
    }
    List(const List<T>& rhs) {
        this->head = this->last = new ListNode<T>();
        this->n = 0;
        for (ListNode<T> *node = rhs.head; node != NULL; node = node->next)
            this->insert(node->item);
    }
    ~List() { delete head; }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    struct ListIter  {
    private:
        ListNode<T> *node;
    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        ListIter(ListNode<T> *ptr) : node(ptr) {}
        reference operator*() const { return node->item; }
        ListIter& operator++() { node = node->next; return *this; }  
        ListIter operator++(int) { ListIter tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const ListIter& a, const ListIter& b) { return a.node == b.node; };
        friend bool operator!= (const ListIter& a, const ListIter& b) { return a.node != b.node; };  
    };

    ListIter begin() { return head->next; }
    ListIter end()   { return NULL; }

    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds on lookup");
        ListNode<T> *node = head->next;
        if (i == n - 1)
            node = last;
        else
            while (i--)
                node = node->next;
        return node->item;
    }

    void push(T item) { insert(0, item); }
    void insert(T item) { insert(n, item); }
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds on insert");
        ListNode<T> *inserted = new ListNode<T>(item);
        if (i == n) {
            last->next = inserted;
            last = inserted;
        } else {
            ListNode<T> *current;
            for (current = head; i > 0; --i)
                current = current->next;
            inserted->next = current->next;
            current->next = inserted;
        }
        ++n;
    }

    T pop() { return remove(0); }
    T remove(size_t i)  {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds on remove");
        if (n == 0)
            throw std::runtime_error("list is empty");
        ListNode<T> *removed = NULL;
        ListNode<T> *current;
        for (current = head; i > 0; --i)
            current = current->next;
        removed = current->next;
        current->next = removed->next;
        if (current->next == NULL) 
            last = current;
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    void remove_item(T &item) {
        ListNode<T> *removed = NULL;
        ListNode<T> *current;
        for (current = head; current->next != NULL && current->next->item != item;)
            current = current->next;
        removed = current->next;
        current->next = removed->next;
        if (current->next == NULL)
            last = current;
        --n;
        removed->next = NULL;
        delete removed;
    }

    friend std::ostream& operator<<(std::ostream& os, List<T>& list) {
        os << "[";
        for (ListNode<T> *current = list.head->next; current != NULL; current = current->next)
            if (current == list.head->next)
                os << current->item;
            else
                os << "," << current->item;
        os << "]";
        return os;
    }
};

#endif
