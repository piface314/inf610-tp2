#include "adj-matrix.hpp"


AdjMatrix::AdjMatrix(size_t v_max) : v_max(v_max) {
    m = new size_t[v_max*v_max];
    for (size_t i = 0; i < v_max*v_max; ++i)
        m[i] = 0;
}

AdjMatrix::~AdjMatrix() {
    delete[] m;
}

void AdjMatrix::add_edge(size_t u, size_t v) {
    ++m[u*v_max + v];
    ++m[v*v_max + u];
}

List<size_t> AdjMatrix::neighbors(size_t u) {
    List<size_t> n;
    for (size_t v = 0; v < v_max; ++v)
        if (m[u*v_max + v])
            n.insert(v);
    return n;
}
