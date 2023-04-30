#include "adj-matrix.hpp"


AdjMatrix::AdjMatrix(size_t v_max) : GraphRep(v_max) {
    m = new size_t[v_max*v_max]{};
}

AdjMatrix::~AdjMatrix() {
    delete[] m;
}

std::unique_ptr<GraphRep> AdjMatrix::copy() {
    AdjMatrix *rep = new AdjMatrix(v_max);
    for (size_t i = 0; i < v_max*v_max; ++i)
        rep->m[i] = m[i];
    std::copy(vertex_map, vertex_map + v_max, rep->vertex_map);
    return std::unique_ptr<AdjMatrix>(rep);
}

size_t AdjMatrix::n_edges() {
    size_t d = 0;
    for (size_t i = 0; i < v_max*v_max; ++i)
        d += m[i];
    return d/2;
}

size_t AdjMatrix::degree(size_t v) {
    size_t d = 0;
    for (size_t u = 0; u < v_max; ++u) {
++op;   d += m[v*v_max + u];
    }
    return d;
}

List<size_t> AdjMatrix::edges(size_t v) {
    List<size_t> edges;
    for (size_t u = 0; u < v_max; ++u) {
        size_t e = (u == v) ? m[v*v_max + u]/2 : m[v*v_max + u];
        for (size_t i = 0; i < e; ++i) {
++op;       edges.insert(u);
        }
    }
    return edges;
}

size_t AdjMatrix::next_edge(size_t u) {
    for (size_t v = 0; v < v_max; ++v) {
++op;   if (m[u*v_max + v])
            return v;
    }
    return v_max;
}

void AdjMatrix::add_edge(size_t u, size_t v) {
++op; ++m[u*v_max + v], ++m[v*v_max + u];
    add_vertex(u), add_vertex(v);
}

void AdjMatrix::del_edge(size_t u, size_t v) {
++op; --m[u*v_max + v], --m[v*v_max + u];
}

void AdjMatrix::clear_edges(size_t v) {
    for (size_t u = 0; u < v_max; ++u) {
++op;   m[v*v_max+u] = 0, m[u*v_max+v] = 0;
    }
}

bool AdjMatrix::adjacent(size_t u, size_t v) {
    return m[u*v_max + v] && m[v*v_max + u];
}