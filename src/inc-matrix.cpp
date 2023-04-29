#include "inc-matrix.hpp"


IncMatrix::IncMatrix(size_t v_max) : GraphRep(v_max) { }
IncMatrix::~IncMatrix() {
    for (auto e : m)
        delete[] e;
}

std::unique_ptr<GraphRep> IncMatrix::copy() {
    IncMatrix *rep = new IncMatrix(v_max);
    for (auto e : m) {
        uint8_t *e_copy = new uint8_t[v_max];
        std::copy(e, e + v_max, e_copy);
        rep->m.insert(e_copy);
    }
    std::copy(vertex_map, vertex_map + v_max, rep->vertex_map);
    return std::unique_ptr<IncMatrix>(rep);
}

size_t IncMatrix::n_edges() { return m.size(); }

size_t IncMatrix::degree(size_t v) {
    size_t d = 0;
    for (auto e : m)
        d += e[v];
    return d;
}

List<size_t> IncMatrix::edges(size_t v) {
    List<size_t> edges;
    for (auto e : m) {
        if (!e[v])
            continue;
        if (e[v] > 1) {
            edges.insert(v);
            continue;
        }
        for (size_t u = 0; u < v_max; ++u)
            if (e[u] && u != v) {
                edges.insert(u);
                break;
            }
    }
    return edges;
}

size_t IncMatrix::next_edge(size_t v) {
    for (auto e : m) {
        if (!e[v])
            continue;
        if (e[v] > 1)
            return v;
        for (size_t u = 0; u < v_max; ++u)
            if (e[u] && u != v)
                return u;
    }
    return v_max;
}

void IncMatrix::add_edge(size_t u, size_t v) {
    uint8_t *edge = new uint8_t[v_max]{};
    ++edge[u], ++edge[v];
    m.insert(edge);
    add_vertex(u), add_vertex(v);
}

void IncMatrix::del_edge(size_t u, size_t v) {
    for (auto e = m.begin(); e != m.end(); ++e)
        if ((*e)[u] && (*e)[v]) {
            m.remove_at(e);
            return;
        }
}

void IncMatrix::clear_edges(size_t v) {
    for (auto e = m.begin(); e != m.end(); ++e)
        if ((*e)[v])
            m.remove_at(e);
}

bool IncMatrix::adjacent(size_t u, size_t v) {
    for (auto e : m)
        if (e[u] && e[v])
            return true;
    return false;
}