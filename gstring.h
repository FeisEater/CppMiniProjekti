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

const StringSize minSize = 11;

class GString
{
    private:
        void fitMoreCharacters(StringSize additionalChars);
        void shrinkCharContainer();
        void replaceCharContainer(StringSize newSize);
        StringSize size;
        StringSize space;
        Character* chars;
        
        class Iterator
        {
        private:
            const GString& string;
            StringSize index;
            void checkIndex();
        public:
            Iterator(const GString& str, StringSize i) : string(str), index(i) {}
            Iterator(Iterator const& it) : string(it.string), index(it.index) {}
            Character& operator*();
            Character* operator->();
            Iterator& operator++();
            Iterator operator++(int);
            friend bool operator==(Iterator const& a, Iterator const& b) {return a.index == b.index;}
            friend bool operator!=(Iterator const& a, Iterator const& b) {return !(a == b);}
        };    
    public:
        GString() : size(0), space(minSize), chars(new Character[minSize]) {check();}
        GString(GString const& string);
        GString(GString&& string);
        GString(const char* s);
        ~GString() {delete[] chars;}
        StringSize getSize() const   {return size;}
        Character &operator[](StringSize i) const;
        GString& operator=(GString const& string);
        GString& operator=(GString&& string);
        friend GString operator+(const GString& s1, const GString& s2);
        GString& operator+=(const GString& s2);
        void push_back(const Character c);
        const Character pop_back();
        void insert(StringSize pos, const GString& string);
        void insert(StringSize pos, const Character c);
        void erase(StringSize start, StringSize end);
        friend std::istream& operator>>(std::istream& is, GString& obj);
        friend std::ostream& operator<<(std::ostream& os, const GString& obj);
        Iterator begin() const {return Iterator(*this, 0);}
        Iterator end() const {return Iterator(*this, size);}
        Iterator begin() {return Iterator(*this, 0);}
        Iterator end() {return Iterator(*this, size);}
        friend void swap (GString& s1, GString& s2);
        void check();

};

bool operator==(GString const& a, GString const& b);
inline bool operator!=(GString const& a, GString const& b)  {return !(a == b);}
bool operator<(GString const& a, GString const& b);
inline bool operator>(GString const& a, GString const& b)  {return b < a;};
inline bool operator<=(GString const& a, GString const& b) {return a == b || a < b;}
inline bool operator>=(GString const& a, GString const& b) {return b <= a;};

#endif	/* GSTRING_H */

