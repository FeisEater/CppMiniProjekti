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

typedef char Character;

class GString
{
    public:
        GString() : size(0), chars(nullptr) {}
        GString(GString const& string);
        GString(const char* s);
        ~GString() {delete[] chars;}
        int getSize() const   {return size;}
        Character &operator[](int i) const;
        GString& operator=(GString const& string);
        friend GString operator+(const GString& s1, const GString& s2);
        friend GString operator+=(GString& s1, const GString& s2);
        friend std::ostream& operator<<(std::ostream& os, const GString& obj)
            {return os << obj.chars;}
        const Character* begin() {return chars;}
        const Character* end() {return chars + size;}
    private:
        int size;
        Character* chars;
};

bool operator==(GString const& a, GString const& b);
inline bool operator!=(GString const& a, GString const& b)  {return !(a == b);}

#endif	/* GSTRING_H */

