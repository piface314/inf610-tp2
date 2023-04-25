#include "inc-matrix.hpp"


IncMatrix::IncMatrix(size_t v_max) : v_max(v_max) { }
IncMatrix::~IncMatrix() { }

void IncMatrix::add_edge(size_t u, size_t v) {
    size_t *edge = new size_t[v_max];
    for (size_t i = 0; i < v_max; ++i)
        edge[i] = 0;
    ++edge[u];
    ++edge[v];
    m.insert(edge);
}

List<size_t> IncMatrix::neighbors(size_t u) {
    List<size_t> n;
    for (auto e : m) {
        if (!e[u])
            continue;
        if (e[u] > 1)
            n.insert(u);
        else 
            for (size_t v = 0; v < v_max; ++v)
                if (e[v] && v != u) {
                    n.insert(v);
                    break;
                }
    }
    return n;
}