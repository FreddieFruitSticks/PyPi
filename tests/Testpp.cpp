#include <string>
#include <iostream>
#include <Testpp.h>

void VERIFY(std::string message, bool cond){
    if(!cond){
        std::cout << "TEST: "<< (message) << " " << "FAILED: " << __FILE__<<"line: "<<__LINE__<< std::endl;
    }else{
        std::cout << "TEST: "<< (message) << "... " << "PASSED" << std::endl;
    }
}

void TEST_SUITE(std::string title, void (*f)()){
    std::cout << "=======================" << std::endl;
    std::cout << "RUNNING "<< title << std::endl;
    std::cout << "=======================" << std::endl;    
    (*f)();
}