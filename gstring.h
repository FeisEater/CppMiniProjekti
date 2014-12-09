/* 
 * File:   gstring.h
 * Author: FeisEater
 *
 * Created on November 17, 2014, 10:58 PM
 */

#ifndef GSTRING_H
#define	GSTRING_H

#include <iostream>
#include <stdexcept>
#include <exception>

class assertion_fail: public std::exception
{
    public:
        assertion_fail() : info("Assertion fail") {}
        assertion_fail(const char* string) : info(string) {}
        const char* what() const noexcept {return info;}
    private:
        const char* info;
};

#ifdef NDEBUG
    #define assert(b, msg) ;
#else
    #define assert(b, msg) \
        if (!(b)) throw assertion_fail(msg);
#endif

typedef char Character;
typedef unsigned int StringSize;

class GString
{
    public:
        GString() : size(0), chars(nullptr) {check();}
        GString(GString const& string);
        GString(const char* s);
        ~GString() {delete[] chars;}
        StringSize getSize() const   {return size;}
        Character &operator[](StringSize i) const;
        GString& operator=(GString const& string);
        friend GString operator+(const GString& s1, const GString& s2);
        friend GString& operator+=(GString& s1, const GString& s2);
        friend std::istream& operator>>(std::istream& is, GString& obj);
        friend std::ostream& operator<<(std::ostream& os, const GString& obj);
        const Character* begin() const {return chars;}
        const Character* end() const {return chars + size;}
        friend void swap (GString& s1, GString& s2);
        void check();
    private:
        StringSize size;
        Character* chars;
};

bool operator==(GString const& a, GString const& b);
inline bool operator!=(GString const& a, GString const& b)  {return !(a == b);}
bool operator<(GString const& a, GString const& b);
inline bool operator>(GString const& a, GString const& b)  {return b < a;};
inline bool operator<=(GString const& a, GString const& b) {return a == b || a < b;}
inline bool operator>=(GString const& a, GString const& b) {return b <= a;};

#endif	/* GSTRING_H */

