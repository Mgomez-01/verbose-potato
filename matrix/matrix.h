#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
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
//Operator overloads
matrix& operator*(matrix& b);
matrix& operator-(matrix& b);
matrix& operator+(matrix& b);
matrix& operator/(matrix& b);


private:
std::vector<std::vector<double>> values;
};
#endif