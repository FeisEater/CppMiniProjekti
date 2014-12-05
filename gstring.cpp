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

GString& GString::operator=(GString const& string)
{
    delete[] chars;
    size = string.size;
    chars = new Character[string.size];
    for (int i = 0; i < string.size; i++)
        chars[i] = string.chars[i];
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

GString operator+(const GString& s1, const GString& s2)
{
    GString result;
    result.size = s1.size + s2.size;
    result.chars = new Character[result.size];
    for (int i = 0; i < s1.size; i++)
        result[i] = s1[i];
    for (int i = 0; i < s2.size; i++)
        result[i + s1.size] = s2[i];
    return result;
}

GString operator+=(GString& s1, const GString& s2)
{
    GString olds1 = s1;
    s1.size += s2.size;
    delete[] s1.chars;
    s1.chars = new Character[s1.size];
    for (int i = 0; i < olds1.size; i++)
        s1[i] = olds1[i];
    for (int i = 0; i < s2.size; i++)
        s1[i + olds1.size] = s2[i];    
    return s1;
}

/*std::istream& operator>>(std::ostream& is, const GString& obj)
{
    for ()
    return is;
}*/