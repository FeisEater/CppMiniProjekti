#include <algorithm>
#include "testdriver.h"
#include "gstring.h"
#include <sstream>
#include <string>

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
    const GString string = "iterate this string please";
    const Character correctChars[26] = {'i', 't', 'e', 'r', 'a', 't', 'e', ' ', 't', 'h', 'i', 's', ' ',
        's', 't', 'r', 'i', 'n', 'g', ' ', 'p', 'l', 'e', 'a', 's', 'e'};
    int i = 0;
    for (Character c : string)
    {
        td.check<Character>(c, correctChars[i]);
        ++i;
    }
    td.check<int>(i, string.getSize());
}

test(swapping, td)
    GString first = "first";
    GString second = "second";
    swap(first, second);
    td.check<GString>(second, "first");
    td.check<GString>(first, "second");
}

test(streamIO, td)
    std::stringstream ss;
    const GString string = "output this";
    const GString string2 = " and this";
    ss << string << string2;
    td.check<std::string>(ss.str(), "output this and this");
    ss.str("takeThisString alsoThisString but ignore this string");
    GString s1, s2;
    ss >> s1 >> s2;
    td.check<GString>(s1, "takeThisString");
    td.check<GString>(s2, "alsoThisString");
}

test(lessThan, td)
    const GString first = "first";
    const GString second = "second";
    td.check<bool>(first < second, true);
    td.check<bool>(second < first, false);
    const GString aaaaa = "aaaaa";
    const GString aaaab = "aaaab";
    td.check<bool>(aaaaa < aaaab, true);
    td.check<bool>(aaaab < aaaaa, false);
    const GString string = "string";
    const GString str = "str";
    td.check<bool>(str < string, true);
    td.check<bool>(string < str, false);
    const GString string2 = "string";
    td.check<bool>(string < string2, false);
    td.check<bool>(string2 < string, false);
}

test(stlSort, td)
    std::vector<GString> v = {"apple", "orange", "pear", "sandwich", "zoidberg", "orangutang", "chocolate"};
    std::vector<GString> ordered = {"apple", "chocolate", "orange", "orangutang", "pear", "sandwich", "zoidberg"};
    for (int i = 0; i < 1000; i++)
    {
        std::random_shuffle(v.begin(), v.end());
        std::sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++)
            td.check<GString>(v[i], ordered[i]);
    }
}

GString f(GString s)   {return s + " <- a GString right there.";}

//Mainly tests compiler, not GString class functionality itself
test(stringFunctionAlsoTakesLiteral, td)
    td.check<GString>(f("creature"), "creature <- a GString right there.");
}

test(pushBack, td)
    GString paul = "paul";
    paul.push_back('a');
    td.check<GString>(paul, "paula");
    paul.push_back(' ');
    paul.push_back('d');
    paul.push_back('e');
    paul.push_back('e');
    paul.push_back('n');
    td.check<GString>(paul, "paula deen");
}

test(popBack, td)
    GString paula = "paula";
    const Character a = paula.pop_back();
    td.check<GString>(paula, "paul");
    td.check<Character>(a, 'a');
    paula.pop_back();
    Character b = 'x';
    td.check<GString>(paula, "pau");
    for (int i = 0; i < 10; i++)
        paula.pop_back();
    b = paula.pop_back();
    td.check<GString>(paula, "");
    td.check<Character>(b, 0);
}

test(insertStuff, td)
    GString string = "thesaurus";
    string.insert(3, ' ');
    td.check<GString>(string, "the saurus");
    string.insert(4, "dino");
    td.check<GString>(string, "the dinosaurus");
    string.insert(0, "-> ");
    string.insert(string.getSize(), " <-");
    td.check<GString>(string, "-> the dinosaurus <-");
    expectException(string.insert(-1, "fail"), std::out_of_range, td)
    expectException(string.insert(string.getSize() + 1, "fail"), std::out_of_range, td)
    endExpectException
    endExpectException
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
        iterators,
        swapping,
        streamIO,
        lessThan,
        stlSort,
        stringFunctionAlsoTakesLiteral,
        pushBack,
        popBack
    });
}
