#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

class Vector {
public:
    Vector(unsigned short int s, const vector<int>& d) : size(s), data(d) {}
    void print() const;

private:
    vector<int> data;
    unsigned short int size;
};

class Matrix {
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);
    friend Matrix operator^(const Matrix&, const Matrix&);
    friend Matrix operator*(const Matrix&, const Matrix&);

public:
    Matrix(unsigned short int r, unsigned short int c, const vector<vector<int>>& d);
    Matrix operator~() const;
    void print() const;
    Vector get_column(unsigned short int c) const;

private:
    unsigned short int row, column;
    vector<vector<int>> data;
};

int main() {
    ifstream in("input.txt");
    if (!in) {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }

    unsigned short int rows, columns;
    in >> rows >> columns;

    vector<vector<int>> elements(rows, vector<int>(columns));
    srand(time(nullptr));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            elements[i][j] = rand() % 9 + 1;
        }
    }

    Matrix m1(rows, columns, elements);
    m1.print();
    cout << endl;

    Vector v = m1.get_column(2);
    v.print();
}

Vector Matrix::get_column(unsigned short int c) const {
    if (c >= column) {
        cerr << "Error: Column index out of bounds!" << endl;
        return Vector(0, {});
    }
    vector<int> d(row);
    for (int i = 0; i < row; i++) {
        d[i] = data[i][c];
    }
    return Vector(row, d);
}

Matrix::Matrix(unsigned short int r, unsigned short int c, const vector<vector<int>>& d) : row(r), column(c), data(d) {}

void Matrix::print() const {
    for (const auto& rowVec : data) {
        for (int val : rowVec) {
            cout << val << '\t';
        }
        cout << endl;
    }
}

void Vector::print() const {
    for (int val : data) {
        cout << val << '\t';
    }
    cout << endl;
}

Matrix Matrix::operator~() const {
    vector<vector<int>> elements(column, vector<int>(row));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            elements[j][i] = data[i][j];
        }
    }
    return Matrix(column, row, elements);
}

Matrix operator+(const Matrix& x, const Matrix& y) {
    if (x.row != y.row || x.column != y.column) {
        cerr << "Error: Matrices must have the same dimensions for addition!" << endl;
        return Matrix(0, 0, {});
    }
    vector<vector<int>> elements(x.row, vector<int>(x.column));
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < x.column; j++) {
            elements[i][j] = x.data[i][j] + y.data[i][j];
        }
    }
    return Matrix(x.row, x.column, elements);
}

Matrix operator-(const Matrix& x, const Matrix& y) {
    if (x.row != y.row || x.column != y.column) {
        cerr << "Error: Matrices must have the same dimensions for subtraction!" << endl;
        return Matrix(0, 0, {});
    }
    vector<vector<int>> elements(x.row, vector<int>(x.column));
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < x.column; j++) {
            elements[i][j] = x.data[i][j] - y.data[i][j];
        }
    }
    return Matrix(x.row, x.column, elements);
}

Matrix operator^(const Matrix& x, const Matrix& y) {
    if (x.row != y.row || x.column != y.column) {
        cerr << "Error: Matrices must have the same dimensions for element-wise multiplication!" << endl;
        return Matrix(0, 0, {});
    }
    vector<vector<int>> elements(x.row, vector<int>(x.column));
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < x.column; j++) {
            elements[i][j] = x.data[i][j] * y.data[i][j];
        }
    }
    return Matrix(x.row, x.column, elements);
}

Matrix operator*(const Matrix& x, const Matrix& y) {
    if (x.column != y.row) {
        cerr << "Error: Matrix multiplication is not possible!" << endl;
        return Matrix(0, 0, {});
    }
    vector<vector<int>> elements(x.row, vector<int>(y.column, 0));
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < y.column; j++) {
            for (int k = 0; k < x.column; k++) {
                elements[i][j] += x.data[i][k] * y.data[k][j];
            }
        }
    }
    return Matrix(x.row, y.column, elements);
}
