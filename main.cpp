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
void check(Type realValue, Type expectedValue);
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
    (void)check<float>(gimmeInt(true), 5);
}

test(sixIsFive)
    (void)check<int>(5, 5);
    (void)check<int>(5, 6);
}

test(fiveIsFive)
    (void)check<int>(5, 5);
    (void)check<int>(4, 4);
}

test(vectorsAreEqual)
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {1,2,3};
    check<vector<int>>(v1, v2);
}

string gimmeString() {return NULL;}
test(nullString)
    (void)check<string>(gimmeString(), "foo");
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
void check(Type realValue, Type expectedValue)
{
    if (realValue != expectedValue)
    {
        cout << curTestName << " failed" << endl;//: expected " << expectedValue << " but was " << realValue << endl;
        throw testfail();
    }
}