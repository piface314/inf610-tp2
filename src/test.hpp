#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "inc-matrix.hpp"
#include "adj-matrix.hpp"
#include "adj-list.hpp"
#include "list.hpp"
#include "test-counter.hpp"


class Test {
private:
    static GraphRep* make_rep(std::string &rep, size_t v_max);
    static void reset();
    static Graph* read_graph(std::ifstream &f, std::string &rep);
public:
    static void run_multi(std::string &problem, std::string &rep, std::string &fp, std::string &fp_out);
    static void run_one(std::string &problem, std::string &rep, std::string &fp);
};

#endif