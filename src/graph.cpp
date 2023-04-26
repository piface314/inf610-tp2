#include "graph.hpp"

Graph::Graph(GraphRep *rep) : rep(rep) { }
Graph::~Graph() { }
void Graph::add_edge(size_t u, size_t v) { rep->add_edge(u, v); }
List<size_t> Graph::neighbors(size_t u) { return rep->neighbors(u); }
size_t Graph::degree(size_t u) { return rep->degree(u); }