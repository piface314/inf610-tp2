#include "test.hpp"

size_t Test::op = 0;

void Test::reset() {
    Test::op = 0;
}

GraphRep *Test::make_rep(std::string &rep, size_t v_max) {
    if (rep == "IncMatrix")
        return new IncMatrix(v_max);
    if (rep == "AdjMatrix")
        return new AdjMatrix(v_max);
    if (rep == "AdjList")
        return new AdjList(v_max);
    throw std::invalid_argument("unknown GraphRep");
}

Graph* Test::read_graph(std::ifstream &f, std::string &rep) {
    if (not f.is_open())
        return NULL;
    size_t v_max, e, u, v;
    if (f >> v_max >> e) {
        Graph *g = new Graph(make_rep(rep, v_max));
        for (size_t i = 0; i < e; ++i) {
            f >> u >> v;
            g->add_edge(u, v);
        }
        return g;
    }
    return NULL;
}

void Test::run_multi(std::string &problem, std::string &rep, std::string &fp, std::string &fp_out) {
    std::ofstream out_f(fp_out);
    if (not out_f.is_open())
        return;
    Graph *g = NULL;
    size_t count = 0;
    out_f << "problem,rep,n_vertices,n_edges,answer,op\n";
    try {
        std::ifstream f(fp);
        if (problem == "euler") {
            while ((g = read_graph(f, rep)) != NULL) {
                size_t n_vertices = g->n_vertices();
                size_t n_edges = g->n_edges();
                std::cout << "Iteration " << count++
                    << " |V| = " << n_vertices << " |E| = " << n_edges << "\n";
                reset();
                auto circuit = g->eulerian_circuit();
                bool answer = !circuit.empty();
                out_f << problem << ',' << rep << ',' << n_vertices << ','
                    << n_edges << ',' << answer << ',' << op << '\n';
                out_f.flush();
            }
            delete g;
            g = NULL;
        } else if (problem == "hamilton") {
            while ((g = read_graph(f, rep)) != NULL) {
                size_t n_vertices = g->n_vertices();
                size_t n_edges = g->n_edges();
                std::cout << "Iteration " << count++
                    << " |V| = " << n_vertices << " |E| = " << n_edges << "\n";
                reset();
                bool answer = g->can_be_hamiltonian();
                out_f << problem << ',' << rep << ',' << n_vertices << ','
                    << n_edges << ',' << answer << ',' << op << '\n';
                out_f.flush();
            }
            delete g;
            g = NULL;
        }
        f.close();
    
        out_f.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        out_f.close();
        exit(1);
    } 
    
}

void Test::run_one(std::string &problem, std::string &rep, std::string &fp) {
    std::ifstream f(fp);
    Graph *g = read_graph(f, rep);
    std::cout << "G using " << rep << " with |V| = " << g->n_vertices()
        << ", |E| = " << g->n_edges() << "\n";
    if (problem == "euler") {
        std::cout <<"Is connected? " << g->is_connected() << "\n";
        bool is_eulerian = g->is_eulerian();
        std::cout <<"Is eulerian? " << is_eulerian << "\n";
        if (is_eulerian) {
            reset();
            auto circuit = g->eulerian_circuit();
            std::cout << "Eulerian circuit: " << circuit << "\n";
            std::cout << "Operations: " << op << "\n";
        }
    } else if (problem == "hamilton") {
        reset();
        std::cout << "Can be hamiltonian? " << g->can_be_hamiltonian() << "\n";
        std::cout << "Operations: " << op << "\n";
    }
    delete g;
    f.close();
}