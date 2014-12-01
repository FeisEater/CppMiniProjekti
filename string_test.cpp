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

test(correctSize2, td)
    const GString gstring = "a";
    td.check<int>(gstring.getSize(), 1);
}

test(correctSize3, td)
    const GString gstring = "huge freaking string though not too huge as it was not generated with a loop but rather typed by hand so thats why it is not a zillion characters long";
    td.check<int>(gstring.getSize(), 150);
}

test(correctCharacters, td)
    const GString gstring = "hello";
    td.check<Character>(gstring[0], 'h');
    td.check<Character>(gstring[1], 'e');
    td.check<Character>(gstring[2], 'l');
    td.check<Character>(gstring[3], 'l');
    td.check<Character>(gstring[4], 'o');
}

test(indexOutOfRange, td)
    const GString gstring = "hello";
    expectException(Character c = gstring[-1], std::out_of_range, td)
    expectException(Character c = gstring[5], std::out_of_range, td)
    endExpectException
    endExpectException
}

test(changeCharacterAtIndex, td)
    const GString string = "hello";
    td.check<GString>(string, "hello");
    string[4] = 'p';
    td.check<GString>(string, "hellp");
    string[1] = 'a';
    td.check<GString>(string, "hallp");
    expectException(string[5] = 'c', std::out_of_range, td)
    endExpectException
}

test(assigningGStringCopiesIt, td)
    const GString string = "hello";
    GString string2 = "bye";
    string2 = string;
    string2[1] = 'a';
    td.check<GString>(string, "hello");
    td.check<GString>(string2, "hallo");
}

test(cantAccessAnyCharacterOnEmptyString, td)
    const GString string = "";
    td.check<GString>(string, "");
    td.check<int>(string.getSize(), 0);
    expectException(Character c = string[0], std::out_of_range, td)
    expectException(Character c = string[1], std::out_of_range, td)
    endExpectException
    endExpectException
}

test(sumOfStrings, td)
    GString string1 = "hello";
    const GString string2 = " world";
    GString string3 = string1 + string2;
    td.check<GString>(string3, "hello world");
    const GString string4 = " mars";
    string1 += string4;
    td.check<GString>(string1, "hello mars");
    GString string5 = "bye cruel" + string2 + "!";
    td.check<GString>(string5, "bye cruel world!");
    string5 += " I'm going to" + string4;
    td.check<GString>(string5, "bye cruel world! I'm going to mars");
}

test(iterators, td)
    GString string = "iterate this string please";
    Character correctChars[26] = {'i', 't', 'e', 'r', 'a', 't', 'e', ' ', 't', 'h', 'i', 's', ' ',
        's', 't', 'r', 'i', 'n', 'g', ' ', 'p', 'l', 'e', 'a', 's', 'e'};
    int i = 0;
    for (Character c : string)
    {
        td.check<Character>(c, correctChars[i]);
        ++i;
    }
    td.check<int>(i, string.getSize());
}

void runTests()
{
    td.runTests({
        initialization,
        assignmentAndEquality,
        correctSize,
        correctSize2,
        correctSize3,
        correctCharacters,
        indexOutOfRange,
        changeCharacterAtIndex,
        assigningGStringCopiesIt,
        cantAccessAnyCharacterOnEmptyString,
        sumOfStrings,
        iterators
    });
}
