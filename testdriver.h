/* 
 * File:   testdriver.h
 * Author: FeisEater
 *
 * Created on November 16, 2014, 8:27 PM
 */

#ifndef TESTDRIVER_H
#define	TESTDRIVER_H

#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include "nvwa/debug_new.h"

#define test(testname, td) void testname() { td.setTestName(#testname);

class testfail: public std::exception
{
    public:
        virtual void printFailReason() const {}
};

template <typename Type>
class equalityFail: public testfail
{
public:
    equalityFail(Type expected, Type real) : expectedValue(expected), realValue(real) {}
    void printFailReason() const
    {
        std::cout << "expected '" << expectedValue << "' but was '" << realValue << "'";
    }
    const Type expectedValue;
    const Type realValue;
};

class exceptionDidntHappen: public testfail
{
public:
    exceptionDidntHappen(std::string code, std::string exc) : executedCode(code), expectedException(exc) {}
    void printFailReason() const
    {
        std::cout << "expected '" << executedCode << "' to trigger exception '" << expectedException << "'";
    }
    std::string expectedException;
    std::string executedCode;
};

class testdriver
{
    public:
        void runTests(int testCounter, std::vector<void (*)()> tests);
        void runTests(std::vector<void (*)()> tests);
        std::string getTestName() {return curTestName;}
        void setTestName(std::string testName) {curTestName = testName;}
        template <typename Type>
        void check(const Type realValue, const Type expectedValue)
        {
            if (realValue != expectedValue)
                throw equalityFail<Type>(expectedValue, realValue);
        }

    private:
        std::string curTestName;
        int testsPassed;
};

#define expectException(code, exc, td) \
    try \
    { \
        code; \
        throw exceptionDidntHappen(#code, #exc); \
    } \
    catch (exc const& e) \
    {

#define endExpectException \
        return; \
    }

#endif	/* TESTDRIVER_H */

