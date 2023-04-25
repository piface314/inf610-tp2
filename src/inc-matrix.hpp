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
    void add_edge(size_t u, size_t v);
    List<size_t> neighbors(size_t u);
};

#endif
