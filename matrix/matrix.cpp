#include "matrix.h"
#include <iostream>

//constructor makes the initial structure for the matrix and populates the entries with zero's 
matrix::matrix(int m, int n) {
    this->dims = std::make_tuple(m,n);
    for(int i = 0; i < m; i++){
        std::vector<double> temp;
        this->values.push_back(temp);
        for(int j = 0; j < n; j++){
        (this->values)[i].push_back(0);
        }
    }
}
// creates a matrix representation of a scalar, or a one vector. representation of a sign and magnitude only for this constructor
matrix::matrix(){
    std::vector<double> temp;
    this->values.push_back(temp);
    this->values[0].push_back(0);
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
    std::cout << "[\n";
    for(int i = 0; i < m ; i++)
    {
        std::cout << "[";
        if(i < m-1){
            for(int j = 0; j < n; j++)
        {
            if(j < n-1){
                std::cout << this->values[i][j] << ",";
                //std::cout << "inner array val,";//this->values[m] << ",";
            }else
            {
            std::cout << this->values[i][j] << "]";
            }
        }
        std::cout<< std::endl;
        }else{
            for(int j = 0; j < n; j++)
        {
            if(j < n-1){
                std::cout << this->values[i][j] << ",";
                //std::cout << "inner array val,";//this->values[m] << ",";
            }else
            {
            std::cout << this->values[i][j] << "]";
            }
        }
        }
    }
    std::cout << "\n]\n";
}

// printing dims easily
void matrix::print_dims()
{
 std::cout << "dim " << std::get<0>(this->dims) << "x"  << std::get<1>(this->dims) << std::endl;   
}
//Operator overloads
matrix& matrix::operator*(matrix& b){}
matrix& matrix::operator-(matrix& b){}
matrix& matrix::operator+(matrix& b)
{
    if(this->values.size() == b.values.size() && this->values[0].size() == b.values[0].size())
    {
        std::cout << "both are the same dimensions and can be added" << std::endl;
    }else{
        std::cout << "dimensions are different and cannot be added" << std::endl;
    }
}
matrix& matrix::operator/(matrix& b){}
matrix& matrix::operator=(matrix& b){
    std::cout << "matrix equality operator" << std::endl;
    if (this == & b)
    {return *this;}
    this->values = b.values;
    return *this;
}
