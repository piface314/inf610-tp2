#include "graph.hpp"

const VertexCb Graph::vertex_noop = [](size_t v){};
const EdgeCb Graph::edge_noop = [](size_t u, size_t v){};

Graph::Graph(GraphRep *rep) : rep(rep) { }
Graph::Graph(Graph &rhs) { rep = rhs.rep->copy(); }
Graph::~Graph() { }
void Graph::add_edge(size_t u, size_t v) { rep->add_edge(u, v); }
void Graph::del_edge(size_t u, size_t v) { rep->del_edge(u, v); }
void Graph::clear_edges(size_t v) { rep->clear_edges(v); }
List<size_t> Graph::edges(size_t u) { return rep->edges(u); }
List<size_t> Graph::vertices() { return rep->vertices(); }
size_t Graph::next_vertex() { return rep->next_vertex(); }
size_t Graph::next_edge(size_t u) { return rep->next_edge(u); }
size_t Graph::degree(size_t u) { return rep->degree(u); }
size_t Graph::max_vertices() { return rep->max_vertices(); }
size_t Graph::n_vertices() { return rep->n_vertices(); }
size_t Graph::n_edges() { return rep->n_edges(); }
bool Graph::has_vertex(size_t v) { return rep->has_vertex(v); }
void Graph::add_vertex(size_t v) { rep->add_vertex(v); }
void Graph::del_vertex(size_t v) { rep->del_vertex(v); }

void Graph::dfs(size_t v_0, VertexCb process_v, EdgeCb process_e) {
    bool visited[max_vertices()] = {0};
    dfs(v_0, visited, process_v, process_e);
}

bool Graph::dfs(size_t v, bool *visited,
    VertexCb process_v = vertex_noop, EdgeCb process_e = edge_noop) {
    process_v(v);
    visited[v] = true;
    for (auto w : edges(v)) {
        process_e(v, w);
++op;   if (!visited[w])
            if (not dfs(w, visited, process_v, process_e))
                return false;
    }
    return true;
}

void Graph::bfs(size_t v_0, VertexCb process_v, EdgeCb process_e) {
    bool visited[max_vertices()] = {0};
    List<size_t> q;
    q.insert(v_0);
    while (!q.empty()) {
        size_t v = q.pop();
        process_v(v);
        visited[v] = true;
        for (auto w : rep->edges(v)) {
            process_e(v, w);
            if (!visited[w])
                q.insert(w);
        }
    }
}

bool Graph::is_eulerian() {
    if (not is_connected())
        return false;
    for (auto v : vertices()) {
        if (degree(v) % 2 == 1)
            return false;
    }
    return true;
}

bool Graph::is_connected() {
    bool visited[max_vertices()] = {0};
    List<size_t> vs = vertices();
    dfs(vs.top(), visited);
    for (auto v : vs) {
++op;   if (not visited[v])
            return false;
    }
    return true;
}

size_t Graph::n_connected_components() {
    size_t n = 0;
    bool visited[max_vertices()] = {0};
    for (auto v : vertices()) {
        if (visited[v])
            continue;
        dfs(v, visited);
        ++n;
    }
    return n;
}

List<size_t> Graph::eulerian_circuit() {
    List<size_t> circuit;
    if (!is_eulerian())
        return circuit;
    Graph g(*this);
    circuit.insert(g.next_vertex());
    auto v_0 = circuit.begin();
    while (v_0 != circuit.end()) {
        List<size_t> c;
        size_t v = *v_0;
        do {
            c.insert(v);
            size_t u = g.next_edge(v);
            g.del_edge(v, u);
            v = u;
        } while (v != *v_0);
        circuit.concat_at(v_0, c);
        for (; v_0 != circuit.end(); ++v_0)
            if (g.degree(*v_0) > 0)
                break;
    }
    return circuit;
}

bool Graph::can_be_hamiltonian() {
    Graph g(*this);
    List<size_t> vs = g.vertices();
    auto v = vs.begin();
    return g.can_be_hamiltonian(vs, v, 0);
}

bool Graph::can_be_hamiltonian(List<size_t> &vs, List<size_t>::Iterator &v, size_t n) {
    if (n > 0 && n_connected_components() > n)
        return false;
    if (n + 1 >= vs.size())
        return true;
    for (auto u = v; u != vs.end(); ++u) {
        List<size_t> es = edges(*u);
        del_vertex(*u);
        if (not can_be_hamiltonian(vs, ++u, n + 1))
            return false;
        --u;
        for (auto w : es)
            add_edge(*u, w);
    }
    return true;
}
