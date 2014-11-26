#include "gstring.h"

GString::GString(GString const& string) : size(string.size)
{
    chars = new Character[string.size];
    for (int i = 0; i < string.size; i++)
        chars[i] = string.chars[i];
}

GString::GString(const char* s)
{
    //first count the size
    size = 0;
    const char *curChar = s;
    while (*curChar)
    {
        ++curChar;
        ++size;
    }
    //then insert the characters
    chars = new Character[size];
    for (int i = 0; i < size; i++)
    {
        chars[i] = *s;
        ++s;
    }
}

Character &GString::operator[](int i) const
{
    if (i < 0 || i >= size)
        throw std::out_of_range("requested GString character index out of range");
    return chars[i];
}

bool operator==(GString const& a, GString const& b)
{
    if (a.getSize() != b.getSize())
        return false;
    for (int i = 0; i < a.getSize(); ++i)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}