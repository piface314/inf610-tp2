#ifndef GRAPH_REP_H
#define GRAPH_REP_H

#include <memory>
#include "list.hpp"


class GraphRep {
public:
    virtual ~GraphRep() { };
    virtual std::unique_ptr<GraphRep> copy() = 0;
    virtual size_t n_vertices() = 0;
    virtual size_t n_edges() = 0;
    virtual List<size_t> vertices() = 0;
    virtual List<size_t> neighbors(size_t u) = 0;
    virtual size_t degree(size_t u);
    virtual void add_edge(size_t u, size_t v) = 0;
    virtual void del_edge(size_t u, size_t v) = 0;
};

#endif
