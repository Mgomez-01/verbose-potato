#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <tuple>
class matrix {

public:
//constructor
matrix(int m, int n);
//default const
matrix();
//Destructor
~matrix();
// transpose operation
matrix transpose(matrix m);
void print_matrix();
void print_dims();
//Operator overloads
matrix& operator*(matrix& b);
matrix& operator-(matrix& b);
matrix& operator+(matrix& b);
matrix& operator/(matrix& b);
matrix& operator=(matrix& b);


private:
std::vector<std::vector<double>> values;
std::tuple<int,int> dims;
};
#endif