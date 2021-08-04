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
matrix transpose();
matrix indentity();
void print_matrix();
void print_dims();
void insert_element(double value, int m, int n);
//Operator overloads
matrix& operator*(double d);
matrix& operator-(matrix& b);
matrix& operator+(matrix& b);
matrix& operator/(matrix& b);
matrix& operator=(matrix& b);


private:
std::vector<std::vector<double>> values;
std::tuple<int,int> dims;
};
#endif