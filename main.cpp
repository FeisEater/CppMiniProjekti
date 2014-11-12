/* 
 * File:   main.cpp
 * Author: FeisEater
 *
 * Created on November 9, 2014, 12:43 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <cstddef>

using namespace std;

static int testCounter;
/*
 * 
 */

void runTests();
template <typename Type>
Type check(Type realValue, Type expectedValue, string testName);

int main(int argc, char** argv) {
    testCounter = 0;
    try
    {
        runTests();
    }
    catch(exception const& e)
    {
        cout << " failed, code threw following exception:" << endl << e.what() << endl;
    }
    catch( ... )
    {
        cout << " failed, code threw unknown exception" << endl;
    }
    return 0;
}

float gimmeInt(bool fail)
{
    if (fail)
        return 5 / 0;
    return 5;
}

void runTests()
{
    check<float>(gimmeInt(true), 5, "test test");
}

template <typename Type>
Type check(Type realValue, Type expectedValue, string testName)
{
    if (realValue == expectedValue)
        cout << testName << " passed" << endl;
    else
        cout << testName << " failed. Expected " << expectedValue << " but was " << realValue << endl;
}