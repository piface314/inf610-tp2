#include "graph.hpp"

Graph::Graph(GraphRep *rep) : rep(rep) { }
Graph::Graph(Graph &rhs) {
    rep = rhs.rep->copy();
}
Graph::~Graph() { }
void Graph::add_edge(size_t u, size_t v) { rep->add_edge(u, v); }
void Graph::del_edge(size_t u, size_t v) { rep->del_edge(u, v); }
List<size_t> Graph::neighbors(size_t u) { return rep->neighbors(u); }
size_t Graph::degree(size_t u) { return rep->degree(u); }

void Graph::dfs(size_t v_0,
                void (*process_v)(size_t v), void (*process_e)(size_t u, size_t v)) {
    bool visited[rep->n_vertices()] = {0};
    dfs(v_0, visited, process_v, process_e);
}

void Graph::dfs(size_t v, bool *visited,
                void (*process_v)(size_t v), void (*process_e)(size_t u, size_t v)) {
    process_v(v);
    visited[v] = true;
    for (auto w : rep->neighbors(v)) {
        process_e(v, w);
        if (!visited[w])
            dfs(w, visited, process_v, process_e);
    }
}

void Graph::bfs(size_t v_0,
                void (*process_v)(size_t v), void (*process_e)(size_t u, size_t v)) {
    bool visited[rep->n_vertices()] = {0};
    List<size_t> q;
    q.insert(v_0);
    while (!q.empty()) {
        size_t v = q.pop();
        process_v(v);
        visited[v] = true;
        for (auto w : rep->neighbors(v)) {
            process_e(v, w);
            if (!visited[w])
                q.insert(w);
        }
    }
}

bool Graph::is_eulerian() {
    for (auto v : rep->vertices())
        if (rep->degree(v) % 2 == 1)
            return false;
    return true;
}

List<size_t> Graph::eulerian_circuit() {
    List<size_t> circuit;
    if (!is_eulerian())
        return circuit;
    List<size_t> vs = rep->vertices();
    Graph g(*this);
    
    return circuit;
}