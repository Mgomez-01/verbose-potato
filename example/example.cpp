#include "example.h"
#include <string>
#include <iostream>

test::test(){}

void test::doThing(std::string s){
std::cout << s;
}

int main(){
    test t = test();
    std::string s = "sample string from Sample Program Example.cpp\n";
    t.doThing(s);

    return 0;
}