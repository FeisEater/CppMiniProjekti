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
#include <vector>

using namespace std;

/*
 * 
 */

#define test(testname) void testname() { curTestName = #testname;

template <typename Type>
Type check(Type realValue, Type expectedValue);
static string curTestName;

class testfail: public exception
{
};

float gimmeInt(bool fail)
{
    if (fail)
        throw domain_error("arbitrary error");
    return 5;
}

test(noErrors)
    check<float>(gimmeInt(true), 5);
}

test(sixIsFive)
    check<int>(5, 5);
    check<int>(5, 6);
}

test(fiveIsFive)
    check<int>(5, 5);
    check<int>(4, 4);
}

test(vectorsAreEqual)
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {1,2,3};
    if (v1 != v2)
    {
        cout << curTestName << " failed" << endl;
        throw testfail();
    }
    //check<vector<int>>(4, 4);
}

string gimmeString() {return NULL;}
test(nullString)
    check<string>(gimmeString(), "foo");
}

void runTests(int testCounter)
{
    vector<void (*)()> tests = {sixIsFive, noErrors, fiveIsFive, vectorsAreEqual, nullString};
    try
    {
        for (; testCounter < tests.size(); testCounter++)
        {
            tests[testCounter]();
            cout << curTestName << " passed" << endl;
        }
    }
    catch(testfail const& e)
    {
        runTests(testCounter + 1);
    }
    catch(exception const& e)
    {
        cout << curTestName << " failed, code threw following exception: " << e.what() << endl;
        runTests(testCounter + 1);
    }
    catch( ... )
    {
        cout << curTestName << " failed, code threw unknown exception" << endl;
        runTests(testCounter + 1);
    }
}

int main(int argc, char** argv) {
    runTests(0);
    return 0;
}

template <typename Type>
Type check(Type realValue, Type expectedValue)
{
    if (realValue != expectedValue)
    {
        cout << curTestName << " failed" << endl;//: expected " << expectedValue << " but was " << realValue << endl;
        throw testfail();
    }
}