//
// Created by Steven  Ly on 2024-10-13.
//

#ifndef PAGERANK_HPP
#define PAGERANK_HPP

#include "matrix.hpp"
#include <vector>
#include <string>
using namespace std;

class pagerank {
private:
    matrix connectivityMatrix;
    matrix transitionMatrix;

    // Damping Factor
    const double dampingFactor;

    // Threshold for convergence
    const double threshold;

    // Helper to load connectivity matrix from txt file
    void loadConnectivityMatrix(const string& filePath);

    // Helper to create the transition matrix
    matrix makeTransitionMatrix(const double dampingFactor) const;

public:
    // Constructor for pagerank, sets damping factor and convergence threshold
    pagerank(const double dampingFactor = 0.85, const double threshold = 0.001);

    // Calculates the pagerank for all pages
    vector<double> calculatePageRank();

    // Function to print the pagerank results
    void printPageRank(const vector<double>& ranks) const;
};

#endif //PAGERANK_HPP
