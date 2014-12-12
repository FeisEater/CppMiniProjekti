#include "testdriver.h"

using namespace std;

//macro to increase failure count, print info to cout and failLog, and continue with the tests
#define failTestAndPrint(info) \
        ++testsFailed; \
        cout << info; \
        failLog << info; \
        runTests(testCounter + 1, tests);

void testdriver::runTests(int testCounter, testContainer tests)
{
    try
    {
        for (; testCounter < tests.size(); testCounter++)
        {
            tests[testCounter]();
            cout << curTestName << " passed" << endl;
        }
        cout << endl;
        if (testsFailed == 0)
            cout << "Congrats, man! All tests passed.";
        else
            cout << testsFailed << " tests faileds!!! Fix the following:" << endl << endl << failLog.str();
        cout << endl;
    }
    catch(testfail const& e)
    {
        failTestAndPrint(curTestName << " failed: " << e.failReason() << endl)
    }
    catch(exception const& e)
    {
        failTestAndPrint(curTestName << " failed, code threw following exception: " << e.what() << endl)
    }
    catch( ... )
    {
        failTestAndPrint(curTestName << " failed, code threw unknown exception" << endl)
    }
}

void testdriver::runTests(testContainer tests)
{
    testsFailed = 0;
    runTests(0, tests);
}
