//
// Created by Steven  Ly on 2024-10-13.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;

// Tolerance
const double TOLERANCE = 1e-9;

class matrix {
private:
    //  2d vector to store matrix elements
  vector<vector<double> > data;
    // # of rows and cols
  size_t rows, cols;

  public:
    // Default constructor (1x1 matrix initialized to 0.0)
    matrix();

    // Constructor that creates nxn sqr matrix initialized to 0.0
    matrix(size_t n);

    // Constructor that creates a matrix w/ r rows and c columns, initialized to 0.0
    matrix(size_t r, size_t c);

    // Constructor that initializes a sqr matrix from 1D vector of values
    // Size of vector must be an int sqr root (nxn matrix)
    matrix(const vector<double>& values);

    // Copy Constructor
    matrix(const matrix& matrix);

    // Destructor
    ~matrix();

    // Getter: returns value at the specified row and col
    double getValue(size_t row, size_t col) const;

    // Setter: Sets the value at the specified row and col
    void setValue(size_t row, size_t col, double value);

    // Returns # of rows in matrix
    size_t getRows() const;

    // Returns # of cols in matrix
    size_t getCols() const;

    // Clears matrix
    void clear();

    // Addition: adds current matrix to another matrix, assigns result to current
    matrix& operator+=(const matrix& matrix);

    // returns a new matrix that is sum of curr and another matrix
    matrix operator+(const matrix& matrix) const;

    // subtracts another matrix from curr matrix, assigns result to curr
    matrix& operator-=(const matrix& matrix);

    // Subtraction: returns a new matrix that is the difference of curr and another matrix
    matrix operator-(const matrix& matrix) const;

    // Multiplication: returns a new matrix that is product of curr and another matrix
    matrix operator*(const matrix& matrix) const;

    // multiplies the curr matrix by another matrix, assigns result to curr
    matrix& operator*=(const matrix& matrix);

    // Scalar multiplication: returns a new matrix where each element is multiplied by scalar
    matrix operator*(double scalar) const;

    // Assignment operator: assigns one matrix to another using copy and swap
    matrix& operator=(matrix matrix);

    // Equality comparison operator: checks if two matrices are equal
    bool operator==(const matrix& matrix) const;

    // Inequality comparison operator: checks if two matrices are not equal
    bool operator!=(const matrix& matrix) const;

    // Prefix increment operator: increments each value in the matrix by 1.0
    matrix& operator++();

    // Postfix increment operator: increments each value in the matrix by 1.0
    matrix operator++(int);

    // Prefix decrement operator: decrements each value in the matrix by 1.0
    matrix& operator--();

    // Postfix decrement operator: decrements each value in the matrix by 1.0
    matrix operator--(int);  // Postfix decrement

    // Overloaded stream insertion operator: allows printing of the matrix
    friend ostream& operator<<(ostream& os, const matrix& matrix);

    // Swap function: swaps the contents of two matrices
    friend void mySwap(matrix& first, matrix& second);

};



#endif //MATRIX_HPP
