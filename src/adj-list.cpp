#include "adj-list.hpp"


AdjList::AdjList(size_t v_max) : v_max(v_max) {
    m = new List<size_t>[v_max];
}

AdjList::~AdjList() {
    delete[] m;
}

void AdjList::add_edge(size_t u, size_t v) {
    m[u].insert(v);
    m[v].insert(u);
}

List<size_t> AdjList::neighbors(size_t u) {
    List<size_t> n;
    for (auto it : m[u])
        n.insert(it);
    return n;
}

size_t AdjList::degree(size_t u) { return m[u].size(); }