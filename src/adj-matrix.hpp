#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include "graph-rep.hpp"


class AdjMatrix : public GraphRep {
private:
    size_t *m;
    size_t v_max;
    size_t _n_edges;
public:
    AdjMatrix(size_t v_max);
    ~AdjMatrix();
    std::unique_ptr<GraphRep> copy();
    size_t n_vertices();
    size_t n_edges();
    List<size_t> vertices();
    size_t degree(size_t u);
    List<size_t> neighbors(size_t u);
    void add_edge(size_t u, size_t v);
    void del_edge(size_t u, size_t v);
};

#endif
