//
// Created by Steven  Ly on 2024-10-13.
//
#include "matrix.hpp"
#include <iomanip>
using namespace std;

matrix::matrix() : rows(1), cols(1), data(1, vector<double>(1, 0.0)) {}

matrix::matrix(size_t n) : rows(n), cols(n) {
    if (n <= 0) throw invalid_argument("Matrix size must be positive.");
    data.resize(n, vector<double>(n, 0.0));
}

matrix::matrix(size_t r, size_t c) : rows(r), cols(c) {
    if (r <= 0 || c <= 0) throw invalid_argument("Matrix dimensions must be positive.");
    data.resize(r, vector<double>(c, 0.0));
}

matrix::matrix(const vector<double>& values) {
    size_t n = static_cast<size_t>(sqrt(values.size()));
    if (n * n != values.size()) {
        throw invalid_argument("Vector size must have an integer square root.");
    }
    rows = cols = n;
    data.resize(n, vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            data[i][j] = values[i * n + j];
        }
    }
}

matrix::matrix(const matrix& matrix) : rows(matrix.rows), cols(matrix.cols), data(matrix.data) {}

matrix::~matrix() {}

double matrix::getValue(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw out_of_range("Matrix index out of bounds.");
    }
    return data[row][col];
}

void matrix::setValue(size_t row, size_t col, double value) {
    if (row >= rows || col >= cols) {
        throw out_of_range("Matrix index out of bounds.");
    }
    data[row][col] = value;
}

size_t matrix::getRows() const {
    return rows;
}

size_t matrix::getCols() const {
    return cols;
}

void matrix::clear() {
    for (auto& row : data) {
        fill(row.begin(), row.end(), 0.0);
    }
}

matrix matrix::operator+(const matrix& omatrix) const {
    if (rows != omatrix.rows || cols != omatrix.cols) {
        throw invalid_argument("Matrix dimensions must match for addition.");
    }
    matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + omatrix.data[i][j];
        }
    }
    return result;
}

matrix& matrix::operator+=(const matrix& matrix) {
    *this = *this + matrix;
    return *this;
}

matrix matrix::operator-(const matrix& omatrix) const {
    if (rows != omatrix.rows || cols != omatrix.cols) {
        throw invalid_argument("Matrix dimensions must match for subtraction.");
    }
    matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - omatrix.data[i][j];
        }
    }
    return result;
}

matrix& matrix::operator-=(const matrix& matrix) {
    *this = *this - matrix;
    return *this;
}

matrix matrix::operator*(const matrix& omatrix) const {
    if (cols != omatrix.rows) {
        throw invalid_argument("Matrix dimensions must agree for multiplication.");
    }
    matrix result(rows, omatrix.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < omatrix.cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * omatrix.data[k][j];
            }
        }
    }
    return result;
}

matrix& matrix::operator*=(const matrix& matrix) {
    *this = *this * matrix;
    return *this;
}

matrix matrix::operator*(double scalar) const {
    matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

matrix& matrix::operator=(matrix matrix) {
    mySwap(*this, matrix);
    return *this;
}

void mySwap(matrix& first, matrix& second) {
    using std::swap;
    swap(first.rows, second.rows);
    swap(first.cols, second.cols);
    swap(first.data, second.data);
}


bool matrix::operator==(const matrix& matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) return false;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (fabs(data[i][j] - matrix.data[i][j]) > TOLERANCE) {
                return false;
            }
        }
    }
    return true;
}

bool matrix::operator!=(const matrix& matrix) const {
    return !(*this == matrix);
}

matrix& matrix::operator++() {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] += 1.0;
        }
    }
    return *this;
}

matrix matrix::operator++(int) {
    matrix temp(*this);
    ++(*this);
    return temp;
}

matrix& matrix::operator--() {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] -= 1.0;
        }
    }
    return *this;
}

matrix matrix::operator--(int) {
    matrix temp(*this);
    --(*this);
    return temp;
}

ostream& operator<<(ostream& os, const matrix& matrix) {
    for (const auto& row : matrix.data) {
        for (const auto& value : row) {
            os << fixed << setprecision(2) << value << " ";
        }
        os << "\n";
    }
    return os;
}

