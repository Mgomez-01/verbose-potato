#include <iostream>
#include "matrix.h"

int main(){
    //std::cout << "Test\n";
    matrix mat1(5,5);   
    matrix mat2(5,5);   
    mat1.print_matrix();
    mat2.print_matrix();
    
    //mat1.print_dims();
    matrix* res = new matrix();

    res = &(mat1 + mat2);

    return 0;

}