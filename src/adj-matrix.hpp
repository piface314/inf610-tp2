#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include "graph-rep.hpp"


class AdjMatrix : public GraphRep {
private:
    size_t *m;
    size_t v_max;
public:
    AdjMatrix(size_t v_max);
    ~AdjMatrix();
    void add_edge(size_t u, size_t v);
    List<size_t> neighbors(size_t u);
};

#endif
