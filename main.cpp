//
// Created by Steven  Ly on 2024-10-13.
// Steven Ly
// A01383591
//

#include "pagerank.hpp"
#include <iostream>
using namespace std;

int main() {

        pagerank pagerank;

        vector<double> ranks = pagerank.calculatePageRank();

        pagerank.printPageRank(ranks);

    return 0;
}
