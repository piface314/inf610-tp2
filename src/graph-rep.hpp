#ifndef GRAPH_REP_H
#define GRAPH_REP_H

#include "list.hpp"


class GraphRep {
public:
    virtual void add_edge(size_t u, size_t v) = 0;
    virtual List<size_t> neighbors(size_t u) = 0;
    virtual size_t degree(size_t u);
};

#endif
