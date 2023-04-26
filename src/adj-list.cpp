#include "adj-list.hpp"


AdjList::AdjList(size_t v_max) : v_max(v_max) {
    m = new List<size_t>[v_max];
    _n_edges = 0;
}

AdjList::~AdjList() {
    delete[] m;
}

std::unique_ptr<GraphRep> AdjList::copy() {
    AdjList *rep = new AdjList(v_max);
    for (size_t v = 0; v < v_max; ++v)
        rep->m[v] = m[v];
    rep->_n_edges = _n_edges;
    return std::unique_ptr<GraphRep>(rep);
}

size_t AdjList::n_edges() { return _n_edges; }

size_t AdjList::n_vertices() { return v_max; }
List<size_t> AdjList::vertices() {
    List<size_t> vs;
    for (size_t v = 0; v < v_max; ++v)
        vs.insert(v);
    return vs;
}

List<size_t> AdjList::neighbors(size_t u) {
    List<size_t> n;
    for (auto it : m[u])
        n.insert(it);
    return n;
}

size_t AdjList::degree(size_t u) { return m[u].size(); }

void AdjList::add_edge(size_t u, size_t v) {
    m[u].insert(v), m[v].insert(u);
    ++_n_edges;
}

void AdjList::del_edge(size_t u, size_t v) {
    m[u].remove_item(v), m[v].remove_item(u);
    ++_n_edges;
}