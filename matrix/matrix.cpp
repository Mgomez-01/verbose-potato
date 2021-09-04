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
matrix matrix::transpose(){return *this;}
matrix matrix::identity()
{
    if(std::get<0>(this->dims) == std::get<1>(this->dims))
    {
    for(int i = 0; i < std::get<0>(this->dims); i ++)
    {
        for (int j = 0; j < std::get<1>(this->dims); j++)
        {
            if(i == j)
            {this->values[i][j] = 1;}
            else this->values[i][j] = 0;
        }
    }
    }else 
    {std::cout<< "Dimensions do not allow this to be an identity matrix. Must have equal dimensions.\n"
    << "Please create a new square matrix of desired size." << std::endl;}
    return *this;
}
void matrix::print_matrix()
{
    int m = this->values.size();
    int n = this->values[0].size();
    std::cout << "Matrix of " << m << " x " << n << std::endl; 
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
 std::cout << std::get<0>(this->dims) << "x"  << std::get<1>(this->dims) << std::endl;   
}

//insert an element
void matrix::insert_element(double value, int m, int n)
{
    if(m > this->values.size() || n > this->values[0].size())
    {
        std::cout << "incorrect dimensions, specify position as indices in a matrix with the topmost/leftmost element being 1,1 up to m,n\n\n." << std::endl;
    }
    else 
    {
        this->values[m-1][n-1] = value;
    }
}
//Operator overloads
matrix& matrix::operator*(double b) 
{
    for(int i = 0; i < std::get<0>(this->dims); i++)
    {
        for(int j = 0; j < std::get<1>(this->dims); j++)
        {
            this->values[i][j] = this->values[i][j] * b; 
        }
    }
    return *this;
}
matrix& matrix::operator-(matrix& b){return *this;}
matrix& matrix::operator+(matrix& b)
{
    if(this->values.size() == b.values.size() && this->values[0].size() == b.values[0].size())
    {
        std::cout << "both are the same dimensions and can be added" << std::endl;
        for(int i = 0; i < this->values.size(); i++)
        {
            for(int j = 0; j < this->values[0].size(); j++)
            {
                this->values[i][j] = this->values[i][j] + b.values[i][j]; 
            }
        }
    }else{
        std::cout << "dimensions are different and cannot be added" << std::endl;
    }

    return *this;
}
matrix& matrix::operator/(matrix& b){return *this;}
matrix& matrix::operator=(matrix& b){
    std::cout << "matrix equality operator" << std::endl;
    if (this == & b)
    {return *this;}
    this->values = b.values;
    this->dims = b.dims;
    return *this;
}
