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

//Thrown when assert called on condition that fails
class assertion_fail: public std::exception
{
    public:
        assertion_fail() : info("Assertion fail") {}
        assertion_fail(const char* string) : info(string) {}
        const char* what() const noexcept {return info;}
    private:
        const char* info;
};

//Assertion macro
#ifdef NDEBUG
    #define assert(b, msg) ;
#else
    #define assert(b, msg) \
        if (!(b)) throw assertion_fail(msg);
#endif

//Character type of which GString consists of
typedef char Character;
//Type for GString's size and index of char array
typedef unsigned int StringSize;

//GString will not allocate less than this amount of memory for characters
const StringSize minSize = 11;

class GString
{
    private:
        void fitMoreCharacters(StringSize additionalChars);
        void shrinkCharContainer();
        void replaceCharContainer(StringSize newSize);
        void setDefaultValues();
        void restoreValues(const GString& backup);
        
        StringSize size;    //size of GString
        StringSize space;   //space allocated for char array
        Character* chars;   //char array
        
        //Iterator class holds char array index
        class Iterator
        {
        private:
            const GString& string;  //always reference to this GString
            StringSize index;       //index of GString's char array
            void checkIndex();
        public:
            //Constructor
            Iterator(const GString& str, StringSize i) : string(str), index(i) {}
            //Copy constructor
            Iterator(Iterator const& it) : string(it.string), index(it.index) {}
            
            Character& operator*();
            Character* operator->();
            Iterator& operator++();
            Iterator operator++(int);
            friend bool operator==(Iterator const& a, Iterator const& b) {return a.index == b.index;}
            friend bool operator!=(Iterator const& a, Iterator const& b) {return !(a == b);}
        };
        
    public:
        //Default constructor
        GString() : size(0), space(minSize), chars(new Character[minSize]) {check();}
        //Copy constructor
        GString(GString const& string);
        //Move constructor
        GString(GString&& string);
        //Type conversion from c_string
        GString(const char* s);
        //Destructor
        //~GString() {delete[] chars;}
        //Copy assignment
        GString& operator=(GString const& string);
        //Move assignment
        GString& operator=(GString&& string);
        
        StringSize getSize() const   {return size;} //return size of GString
        Character &operator[](StringSize i) const;
        friend GString operator+(const GString& s1, const GString& s2);
        GString& operator+=(const GString& s2);
        void push_back(const Character c);
        const Character pop_back();
        void insert(StringSize pos, const GString& string);
        void insert(StringSize pos, const Character c);
        void erase(StringSize start, StringSize end);
        friend std::istream& operator>>(std::istream& is, GString& obj);
        friend std::ostream& operator<<(std::ostream& os, const GString& obj);
        friend void swap (GString& s1, GString& s2);

        Iterator begin() const {return Iterator(*this, 0);}     //Iterator to first character
        Iterator end() const {return Iterator(*this, size);}    //Iterator to one beyond last character

        void check() const;

};

bool operator==(GString const& a, GString const& b);
inline bool operator!=(GString const& a, GString const& b)  {return !(a == b);}
bool operator<(GString const& a, GString const& b);
inline bool operator>(GString const& a, GString const& b)  {return b < a;};
inline bool operator<=(GString const& a, GString const& b) {return a == b || a < b;}
inline bool operator>=(GString const& a, GString const& b) {return b <= a;};

#endif	/* GSTRING_H */

