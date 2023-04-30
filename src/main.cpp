#include <iostream>
#include "test.hpp"


int main(int argc, char const *argv[]) {
    if (argc <= 4) {
        std::cerr << "Usage:\n\t$ " << argv[0] << " (one|multi) (euler|hamilton)"
            "(IncMatrix|AdjMatrix|AdjList) <input-fp> [<output-fp>]\n";
        return 1;
    }
    std::string mode(argv[1]);
    std::string problem(argv[2]);
    std::string rep(argv[3]);
    std::string fp(argv[4]);
    std::string fp_out;
    if (argc > 5)
        fp_out = argv[5];
    if (mode == "one")
        Test::run_one(problem, rep, fp);
    else if (mode == "multi")
        Test::run_multi(problem, rep, fp, fp_out);
    else {
        std::cerr << "error: unknown mode\n";
        return 1;
    }
    return 0;
}