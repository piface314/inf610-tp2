#include "adj-list.hpp"


AdjList::AdjList(size_t v_max) : GraphRep(v_max) {
    m = new List<size_t>[v_max]{};
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
    std::copy(vertex_map, vertex_map + v_max, rep->vertex_map);
    return std::unique_ptr<GraphRep>(rep);
}

size_t AdjList::n_edges() { return _n_edges; }

List<size_t> AdjList::edges(size_t v) {
    return m[v];
}

size_t AdjList::next_edge(size_t v) {
    return m[v].lookup(0);
}

size_t AdjList::degree(size_t v) { return m[v].size(); }

void AdjList::add_edge(size_t u, size_t v) {
    m[u].insert(v), m[v].insert(u);
    add_vertex(u), add_vertex(v);
    ++_n_edges;
}

void AdjList::del_edge(size_t u, size_t v) {
    if (m[u].remove_by(v) && m[v].remove_by(u))
        --_n_edges;
}

void AdjList::clear_edges(size_t v) {
    for (auto it = m[v].begin(); it != m[v].end(); ++it) {
        m[v].remove_at(it);
        if (v == *it)
            m[v].remove_at(it);
        else
            m[*it].remove_by(v);
        --_n_edges;
    }
}

bool AdjList::adjacent(size_t u, size_t v) {
    for (auto w : m[u])
        if (w == v)
            return true;
    return false;
}