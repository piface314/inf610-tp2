#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include "graph-rep.hpp"


class Graph {
private:
    std::unique_ptr<GraphRep> rep;
    void dfs(size_t v, bool *visited, void (*pv)(size_t v), void (*pe)(size_t u, size_t v));
public:
    Graph(GraphRep *rep);
    Graph(Graph &rhs);
    ~Graph();
    void add_edge(size_t u, size_t v);
    void del_edge(size_t u, size_t v);
    List<size_t> neighbors(size_t u);
    size_t degree(size_t u);
    void dfs(size_t v_0, void (*process_v)(size_t v), void (*process_e)(size_t u, size_t v));
    void bfs(size_t v_0, void (*process_v)(size_t v), void (*process_e)(size_t u, size_t v));
    bool is_eulerian();
    List<size_t> eulerian_circuit();
    bool hamiltonian_necessary_condition() { return false; }
};

#endif
