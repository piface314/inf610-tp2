#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <memory>
#include "graph-rep.hpp"

using VertexCb = std::function<void (size_t)>;
using EdgeCb = std::function<void (size_t, size_t)>;


class Graph {
private:
    std::unique_ptr<GraphRep> rep;
    bool dfs(size_t v, bool *visited, VertexCb pv, EdgeCb pe);
    bool can_be_hamiltonian(List<size_t> &vs, List<size_t>::Iterator &v, size_t n);
public:
    static const VertexCb vertex_noop;
    static const EdgeCb edge_noop;
    Graph(GraphRep *rep);
    Graph(Graph &rhs);
    ~Graph();
    void add_edge(size_t u, size_t v);
    void del_edge(size_t u, size_t v);
    bool has_vertex(size_t v);
    void add_vertex(size_t v);
    void del_vertex(size_t v);
    void clear_edges(size_t v);
    List<size_t> vertices();
    List<size_t> edges(size_t u);
    size_t next_vertex();
    size_t next_edge(size_t u);
    size_t degree(size_t u);
    size_t max_vertices();
    size_t n_vertices();
    size_t n_edges();
    void dfs(size_t v_0, VertexCb process_v, EdgeCb process_e);
    void bfs(size_t v_0, VertexCb process_v, EdgeCb process_e);
    bool is_eulerian();
    bool is_connected();
    size_t n_connected_components();
    List<size_t> eulerian_circuit();
    bool can_be_hamiltonian();
};

#endif
