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

#define test(testname, td) void testname() { td.setTestName(#testname);

class testfail: public std::exception {};

class testdriver
{
    public:
        void runTests(int testCounter, std::vector<void (*)()> tests);
        void runTests(std::vector<void (*)()> tests);
        std::string getTestName() {return curTestName;}
        void setTestName(std::string testName) {curTestName = testName;}
        template <typename Type>
        void check(Type realValue, Type expectedValue)
        {
            if (realValue != expectedValue)
            {
                std::cout << curTestName << " failed: expected " << expectedValue << " but was " << realValue << std::endl;
                throw testfail();
            }
        }
    private:
        std::string curTestName;
        
};

#define expectException(code, exc, td) \
    try \
    { \
        code; \
        std::cout << td.getTestName() << " failed: expected " << #code << " to trigger exception " << #exc << std::endl; \
        throw testfail(); \
    } \
    catch (exc const& e) \
    {

#define endExpectException \
        return; \
    }

#endif	/* TESTDRIVER_H */

