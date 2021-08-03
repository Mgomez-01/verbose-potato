#include "matrix.h"
#include <iostream>

//constructor makes the initial structure for the matrix and populates the entries with zero's 
matrix::matrix(int m, int n) {
    for(int i = 0; i < m; i++){
        std::vector<double> temp;
        this->values.push_back(temp);
        for(int j = 0; j < n; j++){
        (this->values)[i].push_back(j);
        }
    }
}
//Destructor
matrix::~matrix(){}
// transpose operation
matrix matrix::transpose(matrix m){}
void matrix::print_matrix()
{
    int m = this->values.size();
    int n = this->values[0].size();
    std::cout << "Matrix of dim " << m << " x " << n << std::endl; 
}

//Operator overloads
matrix& matrix::operator*(matrix& b){}
matrix& matrix::operator-(matrix& b){}
matrix& matrix::operator+(matrix& b){}
matrix& matrix::operator/(matrix& b){}
