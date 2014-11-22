/* 
 * File:   gstring.h
 * Author: FeisEater
 *
 * Created on November 17, 2014, 10:58 PM
 */

#ifndef GSTRING_H
#define	GSTRING_H

#include <iostream>

class GString
{
    public:
        GString() : size(0), chars(nullptr) {}
        GString(const char* s);
        int getSize() const   {return size;}
        const char &operator[](int i) const   {return chars[i];}
        friend std::ostream& operator<<(std::ostream& os, const GString& obj)
        {
            os << obj.chars;
            return os;
        }
    private:
        int size;
        const char* chars;
};

bool operator==(GString const& a, GString const& b);
inline bool operator!=(GString const& a, GString const& b)
{
    return !(a == b);
}
#endif	/* GSTRING_H */

