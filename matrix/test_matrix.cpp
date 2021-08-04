#include <iostream>
#include "matrix.h"

int main(){
    //std::cout << "Test\n";
    matrix mat1(5,5);   
    matrix mat2(5,5);   
    mat1.print_matrix();
    mat2.print_matrix();
    for(int i = 1; i <= 5; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            mat1.insert_element(i,i,j);   
        }
    } 
    //mat1.print_dims();
    matrix* res = new matrix();
    matrix test;
    res = &(mat1 + mat2);

    res->print_matrix();
    
    std::cout << "before multiply"<< std::endl;

            res = &(*res * 5.0);
    
    std::cout << "after multiply and using test after assignment." << std::endl;
    test = *res;
    test.print_matrix();
    test.indentity();
    std::cout << "after Identity ." << std::endl;
    test.print_matrix();
    return 0;

}