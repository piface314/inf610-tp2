#include <iostream>
#include "graph.hpp"
#include "inc-matrix.hpp"
#include "adj-matrix.hpp"
#include "adj-list.hpp"


int main(int argc, char const *argv[]) {
    Graph g(new IncMatrix(9));
    g.add_edge(3, 3);
    g.add_edge(1, 8);
    g.add_edge(0, 1);
    g.add_edge(8, 5);
    g.add_edge(5, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 2);
    g.add_edge(3, 6);
    g.add_edge(6, 8);
    g.add_edge(8, 7);
    g.add_edge(7, 3);

    std::cout << "omega = " << g.n_connected_components() << "\n";
    std::cout << "Is connected? " << g.is_connected() << "\n";
    bool e = g.is_eulerian();
    std::cout << "Is eulerian? " << e << "\n";
    if (e) {
        List<size_t> c = g.eulerian_circuit();
        std::cout << "Eulerian circuit: " << c << "\n";
    }

    Graph g2(new AdjList(10));
    g2.add_edge(0, 1);
    g2.add_edge(1, 2);
    g2.add_edge(2, 0);
    g2.add_edge(3, 1);
    g2.add_edge(3, 4);
    g2.add_edge(2, 4);
    std::cout << "Can be hamiltonian? " << g2.can_be_hamiltonian() << "\n";

    int a = 0, b = 0;
    std::cout << (a >= b - 1) << "\n";
    std::cout << (a + 1 >= b) << "\n";
    return 0;
}