#ifndef GRAPH_REP_H
#define GRAPH_REP_H

#include <memory>
#include "list.hpp"


class GraphRep {
protected:
    size_t v_max;
    bool *vertex_map;
public:
    GraphRep(size_t v_max) : v_max(v_max) { vertex_map = new bool[v_max]{}; };
    virtual ~GraphRep() { delete[] vertex_map; };
    virtual std::unique_ptr<GraphRep> copy() = 0;
    virtual size_t max_vertices() { return v_max; }
    virtual size_t n_vertices() {
        size_t n = 0;
        for (size_t v = 0; v < v_max; ++v)
            n += vertex_map[v];
        return n;
    };
    virtual size_t n_edges() = 0;
    virtual size_t next_vertex() {
        for (size_t v = 0; v < v_max; ++v)
            if (vertex_map[v])
                return v;
        return v_max;
    }
    virtual List<size_t> vertices() {
        List<size_t> vs;
        for (size_t v = 0; v < v_max; ++v)
            if (vertex_map[v])
                vs.insert(v);
        return vs;
    };
    virtual List<size_t> edges(size_t v) = 0;
    virtual size_t next_edge(size_t v) = 0;
    virtual size_t degree(size_t v) = 0;
    virtual bool has_vertex(size_t v) { return vertex_map[v]; }
    virtual void add_vertex(size_t v) { vertex_map[v] = true; }
    virtual void del_vertex(size_t v) { vertex_map[v] = false; clear_edges(v); }
    virtual void add_edge(size_t u, size_t v) = 0;
    virtual void del_edge(size_t u, size_t v) = 0;
    virtual void clear_edges(size_t v) = 0;
    virtual bool adjacent(size_t u, size_t v) = 0;
};

#endif
