#ifndef GRAPH_H
#define GRAPH_H

#include "graph-rep.hpp"


template <typename T>
class Graph {
    static_assert(std::is_base_of<GraphRep, T>::value, "T must be subclass of GraphRep");
    T rep;
public:
    Graph(size_t v_max) : rep(v_max) { }
    void add_edge(size_t u, size_t v) { rep.add_edge(u, v); }
    List<size_t> neighbors(size_t u) { return rep.neighbors(u); }
    size_t degree(size_t u) { return rep.degree(u); }
};

#endif
