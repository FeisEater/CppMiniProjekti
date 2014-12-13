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
#include <sstream>

/*
 * Macro for declaring test function, also passes test name to testdriver, which is same as function name in code
 * testname - name of the test both in source code and in runtime
 * td - testdriver instance
*/
#define test(testname, td) void testname() { td.setTestName(#testname);

//Abstract class for test failure exception
class testfail: public std::exception
{
    public:
        virtual std::string failReason() const {return "this shouldn't be returned";}
};

//Exception for unexpected values from test
template <typename Type>
class equalityFail: public testfail
{
public:
    equalityFail(Type expected, Type real) : expectedValue(expected), realValue(real) {}
    std::string failReason() const
    {
        std::stringstream ss;
        ss << "expected '" << expectedValue << "' but was '" << realValue << "'";
        return ss.str();
    }
    const Type expectedValue;
    const Type realValue;
};

//Exception for failing when expecting an exception
class exceptionDidntHappen: public testfail
{
public:
    exceptionDidntHappen(std::string code, std::string exc) : executedCode(code), expectedException(exc) {}
    std::string failReason() const
    {
        std::stringstream ss;
        ss << "expected '" << executedCode << "' to trigger exception '" << expectedException << "'";
        return ss.str();
    }
    std::string expectedException;
    std::string executedCode;
};

//typedef for vector for function pointers, ie test container
typedef std::vector<void (*)()> testContainer;

class testdriver
{
    public:
        void runTests(testContainer tc);
        void continueFrom(int testCounter);
        
        std::string getTestName() {return curTestName;}
        void setTestName(std::string testName) {curTestName = testName;}
        
        //Expecting for real value to be same as expected value
        template <typename Type>
        void check(const Type& realValue, const Type& expectedValue)
        {
            if (realValue != expectedValue)
                throw equalityFail<Type>(expectedValue, realValue);
        }

    private:
        testContainer tests;        //this holds test pointers
        std::string curTestName;    //name of the test currently runnning
        int testsFailed;    //amount of tests that failed
        std::stringstream failLog;  //Reprint results of failed tests at the end of the run
};

/*
 * macro for expecting exception from code invokation
 * code - invoked code
 * exc - exception that we're expecting
 * td - testdriver instance
*/
#define expectException(code, exc, td) \
    try \
    { \
        code; \
        throw exceptionDidntHappen(#code, #exc); \
    } \
    catch (exc const& e) \
    {}

#endif	/* TESTDRIVER_H */

