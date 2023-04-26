#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include "graph-rep.hpp"


class Graph {
    std::unique_ptr<GraphRep> rep;
public:
    Graph(GraphRep *rep);
    ~Graph();
    void add_edge(size_t u, size_t v);
    List<size_t> neighbors(size_t u);
    size_t degree(size_t u);
};

#endif
