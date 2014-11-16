/* 
 * File:   main.cpp
 * Author: FeisEater
 *
 * Created on November 9, 2014, 12:43 AM
 */

#include "testdriver.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <cstddef>
#include <vector>

using namespace std;
/*
 * 
 */

testdriver td;

float gimmeInt(bool fail)
{
    if (fail)
        throw domain_error("arbitrary error");
    return 5;
}

test(noErrors, td)
    td.check<float>(gimmeInt(true), 5);
}

test(sixIsFive, td)
    td.check<int>(5, 5);
    td.check<int>(5, 6);
}

test(fiveIsFive, td)
    td.check<int>(5, 5);
    td.check<int>(4, 4);
}

test(vectorsAreEqual, td)
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {1,2,3};
    td.check<vector<int>>(v1, v2);
}

string gimmeString() {return NULL;}
test(nullString, td)
    td.check<string>(gimmeString(), "foo");
}

int main(int argc, char** argv) {
    vector<void (*)()> tests = {sixIsFive, noErrors, fiveIsFive, vectorsAreEqual, nullString};
    td.runTests(0, tests);
    return 0;
}
