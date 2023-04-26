#include "inc-matrix.hpp"


IncMatrix::IncMatrix(size_t v_max) : v_max(v_max) { }
IncMatrix::~IncMatrix() { }

std::unique_ptr<GraphRep> IncMatrix::copy() {
    IncMatrix *rep = new IncMatrix(v_max);
    for (auto e : m) {
        size_t *e_copy = new size_t[v_max];
        std::copy(e, e + v_max, e_copy);
        rep->m.insert(e_copy);
    }
    return std::unique_ptr<IncMatrix>(rep);
}

size_t IncMatrix::n_edges() { return m.size(); }

size_t IncMatrix::n_vertices() { return v_max; }
List<size_t> IncMatrix::vertices() {
    List<size_t> vs;
    for (size_t v = 0; v < v_max; ++v)
        vs.insert(v);
    return vs;
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

void IncMatrix::add_edge(size_t u, size_t v) {
    size_t *edge = new size_t[v_max];
    for (size_t i = 0; i < v_max; ++i)
        edge[i] = 0;
    ++edge[u];
    ++edge[v];
    m.insert(edge);
}

void IncMatrix::del_edge(size_t u, size_t v) {
    size_t *edge = NULL;
    for (auto e : m)
        if (e[u] && e[v]) {
            edge = e;
            break;
        }
    if (edge != NULL)
        m.remove_item(edge);
}