#include "testdriver.h"

using namespace std;

//macro to increase failure count, print info to cout and failLog, and continue with the tests
#define failTestAndPrint(info) \
        ++testsFailed; \
        cout << info; \
        failLog << info; \
        continueFrom(testCounter + 1);

//run test starting from the specified part of the container
void testdriver::continueFrom(int testCounter)
{
    try
    {
        for (; testCounter < tests.size(); testCounter++)
        {
            tests[testCounter]();   //test_fail exceptions caught here
            cout << curTestName << " passed" << endl;
        }
        cout << endl;
        if (testsFailed == 0)
            cout << "Congrats, man! All tests passed.";
        else
            cout << testsFailed << " tests faileds!!! Fix the following:" << endl << endl << failLog.str();
        cout << endl;
    }
    catch(testfail const& e)    //straight-forward test failures
    {
        failTestAndPrint(curTestName << " failed: " << e.failReason() << endl)
    }
    catch(exception const& e)   //unexpected exceptions
    {
        failTestAndPrint(curTestName << " failed, code threw following exception: " << e.what() << endl)
    }
    catch( ... )    //anything else that can be caught
    {
        failTestAndPrint(curTestName << " failed, code threw unknown exception" << endl)
    }
}

//call this to run tests from the beginning
void testdriver::runTests(testContainer tc)
{
    tests = tc;
    testsFailed = 0;
    failLog.str("");
    continueFrom(0);
}