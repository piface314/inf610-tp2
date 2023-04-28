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
        this->head = this->last = new ListNode<T>();
        this->n = 0;
    }
    List(const List<T> &rhs) {
        this->head = this->last = new ListNode<T>();
        this->n = 0;
        for (ListNode<T> *node = rhs.head->next; node != NULL; node = node->next)
            this->insert(node->item);
    }
    List& operator=(const List<T> &rhs) {
        if (this->head->next != NULL)
            delete this->head->next;
        this->n = 0;
        for (ListNode<T> *node = rhs.head->next; node != NULL; node = node->next)
            this->insert(node->item);
        return *this;
    }
    ~List() { delete head; }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    struct ListIter {
        friend class List;
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
        ListIter& operator--() { node = node->prev; return *this; }
        ListIter operator--(int) { ListIter tmp = *this; --(*this); return tmp; }
        friend bool operator== (const ListIter& a, const ListIter& b) { return a.node == b.node; };
        friend bool operator!= (const ListIter& a, const ListIter& b) { return a.node != b.node; };  
    };

    ListIter begin() { return head->next; }
    ListIter end()   { return NULL; }

    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        ListNode<T> *node;
        if (i <= n - i) {
            node = head->next;
            while (i--)
                node = node->next;
        } else {
            node = last;
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
        if (i == n) {
            last->next = inserted;
            inserted->prev = last;
            last = inserted;
        } else {
            ListNode<T> *node;
            if (i <= n - i) {
                node = head;
                while (i--)
                    node = node->next;
            } else {
                node = last->prev;
                while (++i < n)
                    node = node->prev;
            }
            node->next->prev = inserted;
            inserted->next = node->next;
            inserted->prev = node;
            node->next = inserted;
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
        if (i <= n - i) {
            node = head;
            while (i--)
                node = node->next;
        } else {
            node = last->prev;
            while (++i < n)
                node = node->prev;
        }
        removed = node->next;
        if (removed->next != NULL)
            removed->next->prev = node;
        node->next = removed->next;
        if (node->next == NULL) 
            last = node;
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    bool remove_by(T &key) {
        ListNode<T> *node = head;
        while (node->next != NULL && node->next->item != key)
            node = node->next;
        ListNode<T> *removed = node->next;
        if (removed == NULL)
            return false;
        if (removed->next != NULL)
            removed->next->prev = node;
        node->next = removed->next;
        if (node->next == NULL)
            last = node;
        --n;
        removed->next = NULL;
        delete removed;
        return true;
    }

    void concat_at(ListIter &it, List<T> &other) {
        ListNode<T> *node = it.node == NULL ? last : (--it).node;
        ListNode<T> *tail = node->next;
        for (auto item : other) {
            node->next = new ListNode<T>(item);
            node->next->prev = node;
            node = node->next;
        }
        node->next = tail;
        if (tail == NULL)
            last = node;
        else
            tail->prev = node;
        n += other.n;
        if (it.node != NULL)
            ++it;
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
