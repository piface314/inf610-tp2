#include "adj-list.hpp"


AdjList::AdjList(size_t v_max) : GraphRep(v_max) {
    m = new List<size_t>[v_max]{};
}

AdjList::~AdjList() {
    delete[] m;
}

std::unique_ptr<GraphRep> AdjList::copy() {
    AdjList *rep = new AdjList(v_max);
    for (size_t v = 0; v < v_max; ++v)
        rep->m[v] = m[v];
    std::copy(vertex_map, vertex_map + v_max, rep->vertex_map);
    return std::unique_ptr<GraphRep>(rep);
}

size_t AdjList::n_edges() {
    size_t d = 0;
    for (size_t v = 0; v < v_max; ++v)
        d += m[v].size();
    return d/2;
}

List<size_t> AdjList::edges(size_t v) {
++op; return m[v];
}

size_t AdjList::next_edge(size_t v) {
++op; return m[v].top();
}

size_t AdjList::degree(size_t v) {
++op; return m[v].size();
}

void AdjList::add_edge(size_t u, size_t v) {
++op; m[u].insert(v), m[v].insert(u);
    add_vertex(u), add_vertex(v);
}

void AdjList::del_edge(size_t u, size_t v) {
    m[u].remove_by(v), m[v].remove_by(u);
}

void AdjList::clear_edges(size_t v) {
    auto it = m[v].begin();
    while (it != m[v].end()) {
        if (v == *it)
            m[v].remove_at(it);
        else
            m[*it].remove_by(v);
        m[v].remove_at(it);
    }
}

bool AdjList::adjacent(size_t u, size_t v) {
    for (auto w : m[u])
        if (w == v)
            return true;
    return false;
}