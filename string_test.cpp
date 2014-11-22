#include "testdriver.h"
#include "gstring.h"

testdriver td;

test(initialization, td)
    GString gstring;
    td.check<int>(gstring.getSize(), 0);
}

test(assignmentAndEquality, td)
    GString gstring = "hello";
    td.check<GString>(gstring, "hello");
}

test(correctSize, td)
    GString gstring = "hello";
    td.check<int>(gstring.getSize(), 5);
}

void runTests()
{
    td.runTests({
        initialization,
        assignmentAndEquality,
        correctSize
    });
}
