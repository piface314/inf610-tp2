#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include "graph-rep.hpp"


class AdjList : public GraphRep {
private:
    List<size_t> *m;
public:
    AdjList(size_t v_max);
    ~AdjList();
    std::unique_ptr<GraphRep> copy();
    size_t n_edges();
    size_t degree(size_t v);
    List<size_t> edges(size_t v);
    size_t next_edge(size_t v);
    void add_edge(size_t u, size_t v);
    void del_edge(size_t u, size_t v);
    void clear_edges(size_t v);
    bool adjacent(size_t u, size_t v);
};

#endif
