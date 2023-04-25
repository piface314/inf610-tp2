#include <iostream>
#include "graph.hpp"
#include "inc-matrix.hpp"
#include "adj-matrix.hpp"
#include "adj-list.hpp"


int main(int argc, char const *argv[]) {
    Graph<IncMatrix> g(50);
    g.add_edge(0, 5);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(0, 0);
    for (auto it : g.neighbors(0))
        std::cout << it << "\n";
    std::cout << "Degree of 0: " << g.degree(0) << "\n";
    return 0;
}
