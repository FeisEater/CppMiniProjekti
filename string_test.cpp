#include "testdriver.h"
#include "gstring.h"

testdriver td;

test(fiveIsFive, td)
    GString gstring;
    //td.check<int>(5, 5);
    //td.check<int>(4, 6);
}

void runTests()
{
    td.runTests({
        fiveIsFive
    });
}
