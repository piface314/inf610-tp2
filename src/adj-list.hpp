#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include "graph-rep.hpp"


class AdjList : public GraphRep {
private:
    List<size_t> *m;
    size_t v_max;
    size_t _n_edges;
public:
    AdjList(size_t v_max);
    ~AdjList();
    std::unique_ptr<GraphRep> copy();
    size_t n_vertices();
    size_t n_edges();
    List<size_t> vertices();
    size_t degree(size_t u);
    List<size_t> neighbors(size_t u);
    size_t next_neighbor(size_t u);
    void add_edge(size_t u, size_t v);
    void del_edge(size_t u, size_t v);
    bool adjacent(size_t u, size_t v);
};

#endif
