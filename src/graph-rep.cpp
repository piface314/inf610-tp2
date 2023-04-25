#include "graph-rep.hpp"


size_t GraphRep::degree(size_t v) {
    return this->neighbors(v).size();
}
