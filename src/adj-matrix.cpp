#include "adj-matrix.hpp"


AdjMatrix::AdjMatrix(size_t v_max) : v_max(v_max) {
    m = new size_t[v_max*v_max];
    for (size_t i = 0; i < v_max*v_max; ++i)
        m[i] = 0;
    _n_edges = 0;
}

AdjMatrix::~AdjMatrix() {
    delete[] m;
}

std::unique_ptr<GraphRep> AdjMatrix::copy() {
    AdjMatrix *rep = new AdjMatrix(v_max);
    for (size_t i = 0; i < v_max*v_max; ++i)
        rep->m[i] = m[i];
    rep->_n_edges = _n_edges;
    return std::unique_ptr<AdjMatrix>(rep);
}

size_t AdjMatrix::n_edges() { return _n_edges; }

size_t AdjMatrix::n_vertices() { return v_max; }
List<size_t> AdjMatrix::vertices() {
    List<size_t> vs;
    for (size_t v = 0; v < v_max; ++v)
        vs.insert(v);
    return vs;
}

size_t AdjMatrix::degree(size_t u) {
    size_t d = 0;
    for (size_t v = 0; v < v_max; ++v)
        d += m[u*v_max + v];
    return d;
}

List<size_t> AdjMatrix::neighbors(size_t u) {
    List<size_t> n;
    for (size_t v = 0; v < v_max; ++v)
        if (m[u*v_max + v])
            n.insert(v);
    return n;
}

void AdjMatrix::add_edge(size_t u, size_t v) {
    ++m[u*v_max + v], ++m[v*v_max + u];
    ++_n_edges;
}

void AdjMatrix::del_edge(size_t u, size_t v) {
    if (m[u*v_max + v] && m[v*v_max + u])
        --m[u*v_max + v], --m[v*v_max + u];
    --_n_edges;
}