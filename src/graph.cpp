#include "graph.hpp"


Graph::Graph(GraphRep *rep) : rep(rep) { }
Graph::Graph(Graph &rhs) {
    rep = rhs.rep->copy();
}
Graph::~Graph() { }
void Graph::add_edge(size_t u, size_t v) { rep->add_edge(u, v); }
void Graph::del_edge(size_t u, size_t v) { rep->del_edge(u, v); }
List<size_t> Graph::neighbors(size_t u) { return rep->neighbors(u); }
size_t Graph::next_neighbor(size_t u) { return rep->next_neighbor(u); }
size_t Graph::degree(size_t u) { return rep->degree(u); }
size_t Graph::n_vertices() { return rep->n_vertices(); }
size_t Graph::n_edges() { return rep->n_edges(); }

void Graph::dfs(size_t v_0,
                VertexVoidFn process_v, EdgeVoidFn process_e) {
    VertexBoolFn pv = [&](size_t v) { process_v(v); return true; };
    EdgeBoolFn pe = [&](size_t u, size_t v) { process_e(u, v); return true; };
    dfs(v_0, pv, pe);
}

void Graph::dfs(size_t v_0,
                VertexBoolFn process_v, EdgeBoolFn process_e) {
    bool visited[rep->n_vertices()] = {0};
    dfs(v_0, visited, process_v, process_e);
}

bool Graph::dfs(size_t v, bool *visited,
                VertexBoolFn process_v, EdgeBoolFn process_e) {
    if (not process_v(v)) return false;
    visited[v] = true;
    for (auto w : rep->neighbors(v)) {
        if (not process_e(v, w)) return false;
        if (!visited[w])
            if (not dfs(w, visited, process_v, process_e))
                return false;
    }
    return true;
}

void Graph::bfs(size_t v_0,
                VertexVoidFn process_v, EdgeVoidFn process_e) {
    VertexBoolFn pv = [&](size_t v) { process_v(v); return true; };
    EdgeBoolFn pe = [&](size_t u, size_t v) { process_e(u, v); return true; };
    bfs(v_0, pv, pe);
}

void Graph::bfs(size_t v_0,
                VertexBoolFn process_v, EdgeBoolFn process_e) {
    bool visited[rep->n_vertices()] = {0};
    List<size_t> q;
    q.insert(v_0);
    while (!q.empty()) {
        size_t v = q.pop();
        if (not process_v(v)) return;
        visited[v] = true;
        for (auto w : rep->neighbors(v)) {
            if (not process_e(v, w)) return;
            if (!visited[w])
                q.insert(w);
        }
    }
}

bool Graph::is_eulerian() {
    if (not is_connected())
        return false;
    for (auto v : rep->vertices())
        if (rep->degree(v) % 2 == 1) 
            return false;
    return true;
}

bool Graph::is_connected() {
    size_t v_max = rep->n_vertices();
    bool visited[v_max] = {0};
    dfs(0, [&](size_t u){ visited[u] = true; }, [](size_t u, size_t v){});
    for (size_t v = 0; v < v_max; ++v)
        if (not visited[v])
            return false;
    return true;
}

size_t Graph::n_connected_components() {
    size_t n = 0, v_max = rep->n_vertices();
    bool visited[v_max] = {0};
    size_t v_0 = 0;
    while (v_0 < v_max) {
        dfs(v_0, [&](size_t u){ visited[u] = true; }, [](size_t u, size_t v){});
        ++n;
        for (++v_0; v_0 < v_max; ++v_0)
            if (not visited[v_0])
                break;
    }
    return n;
}

List<size_t> Graph::eulerian_circuit() {
    List<size_t> circuit;
    if (!is_eulerian())
        return circuit;
    Graph g(*this);
    size_t v_0 = 0, v_max = rep->n_vertices();
    bool visited[v_max] = {0};
    while (g.n_edges() > 0) {
        List<size_t> c;
        size_t v = v_0;
        do {
            c.insert(v);
            visited[v] = true;
            size_t u = g.next_neighbor(v);
            g.del_edge(v, u);
            v = u;
        } while (v != v_0);
        circuit.patch_by(v_0, c);
        for (v_0 = 0; v_0 < v_max; ++v_0)
            if (g.degree(v_0) > 0 && visited[v_0])
                break;
    }
    circuit.insert(0);
    return circuit;
}