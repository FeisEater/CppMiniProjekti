#include "testdriver.h"
#include "gstring.h"

testdriver td;

test(initialization, td)
    const GString gstring;
    td.check<int>(gstring.getSize(), 0);
}

test(assignmentAndEquality, td)
    const GString gstring = "hello";
    td.check<GString>(gstring, "hello");
}

test(correctSize, td)
    const GString gstring = "hello";
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
