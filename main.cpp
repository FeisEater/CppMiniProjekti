/* 
 * File:   main.cpp
 * Author: FeisEater
 *
 * Created on November 9, 2014, 12:43 AM
 */

#include "string_test.h"
#include "gstring.h"
#include <iostream>
/*
 * 
 */

int main(int argc, char** argv) {
    GString s;
    std::cin >> s;
    std::cout << "'" << s << "'" << std::endl;
    runTests();
    return 0;
}
