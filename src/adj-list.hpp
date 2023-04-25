#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include "graph-rep.hpp"


class AdjList : public GraphRep {
private:
    List<size_t> *m;
    size_t v_max;
public:
    AdjList(size_t v_max);
    ~AdjList();
    void add_edge(size_t u, size_t v);
    List<size_t> neighbors(size_t u);
    size_t degree(size_t u);
};

#endif
