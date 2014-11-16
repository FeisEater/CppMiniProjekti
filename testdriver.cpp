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
        }
    }
    catch(testfail const& e)
    {
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
