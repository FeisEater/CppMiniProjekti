#include "testdriver.h"

using namespace std;

void testdriver::runTests(int testCounter, vector<void (*)()> tests)
{
    try
    {
        for (; testCounter < tests.size(); testCounter++)
        {
            tests[testCounter]();
            cout << curTestName << " passed" << endl;
            ++testsPassed;
        }
        cout << endl;
        if (testsPassed == tests.size())
            cout << "Congrats, man! All tests passed.";
        else
            cout << (tests.size() - testsPassed) << " tests faileds!!!";
        cout << endl;
    }
    catch(testfail const& e)
    {
        cout << curTestName << " failed: ";
        e.printFailReason();
        cout << endl;
        runTests(testCounter + 1, tests);
    }
    catch(exception const& e)
    {
        cout << curTestName << " failed, code threw following exception: " << e.what() << endl;
        runTests(testCounter + 1, tests);
    }
    catch( ... )
    {
        cout << curTestName << " failed, code threw unknown exception" << endl;
        runTests(testCounter + 1, tests);
    }
}

void testdriver::runTests(vector<void (*)()> tests)
{
    testsPassed = 0;
    runTests(0, tests);
}
