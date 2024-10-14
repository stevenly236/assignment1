//
// Created by Steven  Ly on 2024-10-13.
//

#include "pagerank.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

pagerank::pagerank(const double dampingFactor, const double threshold)
: dampingFactor(dampingFactor), threshold(threshold) {
    loadConnectivityMatrix("../connectivity.txt");
}

void pagerank::loadConnectivityMatrix(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filePath << endl;
        exit(1);
    }

    vector<double> connectivityValues;
    double value;
    while (file >> value) {
        connectivityValues.push_back(value);
    }

    connectivityMatrix = matrix(connectivityValues);
    file.close();
}

matrix pagerank::makeTransitionMatrix(const double dampingFactor) const {
    size_t n = connectivityMatrix.getRows();
    matrix stochasticMatrix = connectivityMatrix;
    matrix randomWalkMatrix(n, n);


    for (size_t col = 0; col < n; ++col) {
        double colSum = 0;
        for (size_t row = 0; row < n; ++row) {
            colSum += connectivityMatrix.getValue(row, col);
        }

        if (colSum == 0) {
            for (size_t row = 0; row < n; ++row) {
                stochasticMatrix.setValue(row, col, 1.0 / n);
            }
        } else {
            for (size_t row = 0; row < n; ++row) {
                stochasticMatrix.setValue(row, col, connectivityMatrix.getValue(row, col) / colSum);
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            randomWalkMatrix.setValue(i, j, 1.0 / n);
        }
    }

    return stochasticMatrix * dampingFactor + randomWalkMatrix * (1 - dampingFactor);
}

   vector<double> pagerank::calculatePageRank() {
    size_t n = connectivityMatrix.getRows();
    transitionMatrix = makeTransitionMatrix(dampingFactor);


    vector<double> rank(n, 1.0);
    bool converged = false;

    while (!converged) {
            vector<double> newRank(n, 0.0);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                newRank[i] += transitionMatrix.getValue(i, j) * rank[j];
            }
        }

        converged = true;
        for (size_t i = 0; i < n; ++i) {
            if (fabs(newRank[i] - rank[i]) > threshold) {
                converged = false;
            }
        }

        rank = newRank;
    }

    double sum = 0;
    for (double r : rank) {
        sum += r;
    }
    for (double& r : rank) {
        r /= sum;
    }

    return rank;
}

void pagerank::printPageRank(const vector<double>& ranks) const {
    size_t numPages = connectivityMatrix.getRows();
    for (size_t i = 0; i < numPages; ++i) {
        char pageLabel = 'A' + i;
        cout << "Page " << pageLabel << ": " << fixed << setprecision(2) << ranks[i] * 100 << "%" << endl;
    }
}