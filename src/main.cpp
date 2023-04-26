#include <iostream>
#include "graph.hpp"
#include "inc-matrix.hpp"
#include "adj-matrix.hpp"
#include "adj-list.hpp"


int main(int argc, char const *argv[]) {
    Graph g(new IncMatrix(50));
    g.add_edge(0, 5);
    g.add_edge(0, 2);
    Graph g2(g);
    g2.del_edge(0, 5);
    g.add_edge(1, 2);
    g.add_edge(0, 0);
    for (auto it : g.neighbors(0))
        std::cout << it << "\n";

    std::cout << "DFS\n";
    g.dfs(0, [](size_t v) {
        std::cout << "Visited vertex " << v << "\n";
    }, [](size_t u, size_t v) {
        std::cout << "Visited edge " << u << "," << v << "\n";
    });

    std::cout << "BFS\n";
    g.bfs(0, [](size_t v) {
        std::cout << "Visited vertex " << v << "\n";
    }, [](size_t u, size_t v) {
        std::cout << "Visited edge " << u << "," << v << "\n";
    });

    std::cout << "BFS\n";
    g2.bfs(0, [](size_t v) {
        std::cout << "Visited vertex " << v << "\n";
    }, [](size_t u, size_t v) {
        std::cout << "Visited edge " << u << "," << v << "\n";
    });
    return 0;
}
