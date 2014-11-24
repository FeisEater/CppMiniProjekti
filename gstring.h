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
        GString(const Character* s);
        int getSize() const   {return size;}
        const Character &operator[](int i) const;
        friend std::ostream& operator<<(std::ostream& os, const GString& obj)
            {return os << obj.chars;}
    private:
        int size;
        const Character* chars;
};

bool operator==(GString const& a, GString const& b);
inline bool operator!=(GString const& a, GString const& b)  {return !(a == b);}

#endif	/* GSTRING_H */

