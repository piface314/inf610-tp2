#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include "graph-rep.hpp"


class IncMatrix : public GraphRep {
private:
    List<size_t*> m;
    size_t v_max;
public:
    IncMatrix(size_t v_max);
    ~IncMatrix();
    std::unique_ptr<GraphRep> copy();
    size_t n_vertices();
    size_t n_edges();
    List<size_t> vertices();
    List<size_t> neighbors(size_t u);
    void add_edge(size_t u, size_t v);
    void del_edge(size_t u, size_t v);
};

#endif
