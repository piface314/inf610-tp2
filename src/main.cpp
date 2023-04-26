#include <iostream>
#include "graph.hpp"
#include "inc-matrix.hpp"
#include "adj-matrix.hpp"
#include "adj-list.hpp"


int main(int argc, char const *argv[]) {
    Graph g(new IncMatrix(5));
    g.add_edge(0, 3);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(1, 0);
    g.add_edge(0, 0);
    g.add_edge(3, 4);
    g.add_edge(0, 4);

    std::cout << "Is connected? " << g.is_connected() << "\n";
    std::cout << "Is eulerian? " << g.is_eulerian() << "\n";
    std::cout << "omega = " << g.n_connected_components() << "\n";
    return 0;
}
