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

test(inequality, td)
    const GString gstring = "one thing";
    const GString gstring2 = "one thing";
    const GString gstring3 = "another";
    td.check<bool>(gstring != gstring2, false);
    td.check<bool>(gstring != gstring3, true);
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
}

test(changeCharacterAtIndex, td)
    const GString string = "hello";
    td.check<GString>(string, "hello");
    string[4] = 'p';
    td.check<GString>(string, "hellp");
    string[1] = 'a';
    td.check<GString>(string, "hallp");
}

test(cantChangeCharacterOutOfRange, td)
    const GString string = "hello";
    expectException(string[5] = 'c', std::out_of_range, td)
}

test(assigningGStringCopiesIt, td)
    const GString string = "hello";
    GString string2 = "bye";
    string2 = string;
    string2[1] = 'a';
    td.check<GString>(string, "hello");
    td.check<GString>(string2, "hallo");
}

test(cpConstructingGStringCopiesIt, td)
    const GString string = "hello";
    GString string2(string);
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
}

test(sumOfStrings, td)
    const GString string1 = "hello";
    const GString string2 = " world";
    GString string3 = string1 + string2;
    td.check<GString>(string3, "hello world");
}

test(sumOfStrings2, td)
    GString string1 = "hello";
    const GString string4 = " mars";
    string1 += string4;
    td.check<GString>(string1, "hello mars");
}

test(sumOfStrings3, td)
    const GString string2 = " world";    
    const GString string5 = "bye cruel" + string2 + "!";
    td.check<GString>(string5, "bye cruel world!");
}

test(sumOfStrings4, td)
    const GString string2 = " world";    
    GString string5 = "bye cruel" + string2 + "!";
    const GString string4 = " mars";
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
}

test(iterateCorrectAmount, td)
    const GString string = "iterate this string please";
    int i = 0;
    for (Character c : string)  ++i;
    td.check<int>(i, string.getSize());
}

test(setValuesViaIterator, td)
    GString aaaa = "123456";
    //Why doesn't setting a value work with 'for (Character c : aaaa)'?
    for (auto it = aaaa.begin(); it != aaaa.end(); ++it)
        *it = 'a';
    td.check<GString>(aaaa, "aaaaaa");
}

test(swapping, td)
    GString first = "first";
    GString second = "second";
    swap(first, second);
    td.check<GString>(second, "first");
    td.check<GString>(first, "second");
}

test(streamOutput, td)
    std::stringstream ss;
    const GString string = "output this";
    const GString string2 = " and this";
    ss << string << string2;
    td.check<std::string>(ss.str(), "output this and this");
}

test(streamInput, td)
    std::stringstream ss;
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
}

test(lessThan2, td)
    const GString aaaaa = "aaaaa";
    const GString aaaab = "aaaab";
    td.check<bool>(aaaaa < aaaab, true);
    td.check<bool>(aaaab < aaaaa, false);
}

test(lessThan3, td)
    const GString string = "string";
    const GString str = "str";
    td.check<bool>(str < string, true);
    td.check<bool>(string < str, false);
}

test(lessThan4, td)
    const GString string = "string";
    const GString string2 = "string";
    td.check<bool>(string < string2, false);
    td.check<bool>(string2 < string, false);
}

test(stlSort, td)
    std::vector<GString> v = {"apple", "orange", "pear", "sandwich", "zoidberg", "orangutang", "chocolate"};
    std::vector<GString> ordered = {"apple", "chocolate", "orange", "orangutang", "pear", "sandwich", "zoidberg"};
    for (int i = 0; i < 50; i++)
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
}

test(pushBack2, td)
    GString paul = "paula";    
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
}

test(popBack2, td)
    GString paula = "paula";
    paula.pop_back();
    td.check<GString>(paula, "paul");
}

test(popBeyond, td)
    GString paula = "paula";    
    Character b = 'x';
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
}

test(insertStuff2, td)
    GString string = "the saurus";
    string.insert(4, "dino");
    td.check<GString>(string, "the dinosaurus");
}

test(insertStuff3, td)
    GString string = "the dinosaurus";    
    string.insert(0, "-> ");
    string.insert(string.getSize(), " <-");
    td.check<GString>(string, "-> the dinosaurus <-");
}

test(insertStuff4, td)
    GString string = "the dinosaurus";    
    string.insert(0, '!');
    string.insert(string.getSize(), '!');
    td.check<GString>(string, "!the dinosaurus!");
}

test(insertFail, td)
    GString string = "string";
    expectException(string.insert(-1, "fail"), std::out_of_range, td)
    expectException(string.insert(7, "fail"), std::out_of_range, td)
}

test(insertFail2, td)
    GString string = "string";
    expectException(string.insert(-1, 'x'), std::out_of_range, td)
    expectException(string.insert(7, 'x'), std::out_of_range, td)
}

test(eraseStuff, td)
    GString string = "!Carefully erase _this string_ right here!";
    string.erase(17, 30);
    td.check<GString>(string, "!Carefully erase right here!");
}

test(eraseStuff2, td)
    GString string = "fixo the typo";
    string.erase(3, 3);
    td.check<GString>(string, "fix the typo");
}

test(eraseStuff3, td)
    GString string = "!Remove surrounding exclamation marks!";
    string.erase(0, 0);
    string.erase(string.getSize() - 1, string.getSize() - 1);
    td.check<GString>(string, "Remove surrounding exclamation marks");
}

test(eraseFail, td)
    GString string = "0123456789";
    expectException(string.erase(5, 3), std::domain_error, td)
}

test(eraseFail2, td)
    GString string = "0123456789";
    //if StringSize is unsigned, domain_error is thrown instead of out_of_range. just check if any exception is thrown    
    expectException(string.erase(-1, 5), std::exception, td)
}

test(eraseFail3, td)
    GString string = "0123456789";
    expectException(string.erase(8, 10), std::out_of_range, td)
}

test(eraseEverything, td)
    GString string = "No man shall see this string right here";
    string.erase(0, string.getSize() - 1);
    td.check<GString>(string, "");
}

test(cstring, td)
    const GString string = "hello";
    const char* c;
    try
    {
        c = string.to_C_string();
        td.check<char>(c[0], 'h');
        td.check<char>(c[1], 'e');
        td.check<char>(c[2], 'l');
        td.check<char>(c[3], 'l');
        td.check<char>(c[4], 'o');
        td.check<char>(c[5], '\0');
        delete[] c;
    }
    catch(...)  {delete[] c; throw;}
}

test(cstring2, td)
    const GString string;
    const char* c;
    try
    {
        c = string.to_C_string();
        td.check<char>(c[0], '\0');
        delete[] c;
    }
    catch(...)  {delete[] c; throw;}
}

test(subString, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("cat"), true);
}

test(subString2, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("cte"), false);
}

test(subString3, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("dog"), false);
}

test(subString4, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("tac"), false);
}

test(subString5, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("con"), true);
}

test(subString6, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("ate"), true);
}

test(subString7, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring(""), true);
}

test(subString8, td)
    GString string = "concatenate";
    td.check<bool>(string.hasSubstring("concatenate"), true);
}

void runTests()
{
    td.runTests({
        initialization,
        assignmentAndEquality,
        inequality,
        correctSize,
        correctSize2,
        correctSize3,
        correctCharacters,
        indexOutOfRange,
        changeCharacterAtIndex,
        cantChangeCharacterOutOfRange,
        assigningGStringCopiesIt,
        cpConstructingGStringCopiesIt,
        cantAccessAnyCharacterOnEmptyString,
        sumOfStrings,
        sumOfStrings2,
        sumOfStrings3,
        sumOfStrings4,
        iterators,
        iterateCorrectAmount,
        setValuesViaIterator,
        swapping,
        streamOutput,
        streamInput,
        lessThan,
        lessThan2,
        lessThan3,
        lessThan4,
        stlSort,    //if ndebug is not defined, comment this out if you're sick of move construction and assignment reports
        stringFunctionAlsoTakesLiteral,
        pushBack,
        pushBack2,
        popBack,
        popBack2,
        popBeyond,
        insertStuff,
        insertStuff2,
        insertStuff3,
        insertStuff4,
        insertFail,
        insertFail2,
        eraseStuff,
        eraseStuff2,
        eraseStuff3,
        eraseFail,
        eraseFail2,
        eraseFail3,
        eraseEverything,
        cstring,
        cstring2,
        subString,
        subString2,
        subString3,
        subString4,
        subString5,
        subString6,
        subString7,
        subString8,
    });
}
