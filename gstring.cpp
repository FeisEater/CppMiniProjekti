#include "gstring.h"

GString::GString(GString const& string) : size(string.size)
{
    chars = new Character[string.size];
    for (StringSize i = 0; i < string.size; i++)
        chars[i] = string.chars[i];
    check();
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
    for (StringSize i = 0; i < size; i++)
    {
        chars[i] = *s;
        ++s;
    }
    check();
}

Character &GString::operator[](StringSize i) const
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
    for (StringSize i = 0; i < string.size; i++)
        chars[i] = string.chars[i];
    check();
    return *this;
}

bool operator==(GString const& a, GString const& b)
{
    if (a.getSize() != b.getSize())
        return false;
    for (StringSize i = 0; i < a.getSize(); ++i)
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
    for (StringSize i = 0; i < s1.size; i++)
        result[i] = s1[i];
    for (StringSize i = 0; i < s2.size; i++)
        result[i + s1.size] = s2[i];
    result.check();
    return result;
}

GString& operator+=(GString& s1, const GString& s2)
{
    GString olds1 = s1;
    s1.size += s2.size;
    delete[] s1.chars;
    s1.chars = new Character[s1.size];
    for (StringSize i = 0; i < olds1.size; i++)
        s1[i] = olds1[i];
    for (StringSize i = 0; i < s2.size; i++)
        s1[i + olds1.size] = s2[i];
    s1.check();
    return s1;
}

std::ostream& operator<<(std::ostream& os, const GString& obj)
{
    for (Character c : obj)
        os << c;
    return os;
}

bool isWhiteSpace(Character c)
{
    const Character whitespaces[6] = {' ', '\f', '\n', '\r', '\t', '\v'};
    for (Character w : whitespaces)
        if (c == w) return true;
    return false;
}

std::istream& operator>>(std::istream& is, GString& obj)
{
    obj = "";
    Character c;
    is.get(c);
    while(c && !isWhiteSpace(c))
    {
        obj += &c;
        is.get(c);
    }
    obj.check();
    return is;
}

void swap (GString& s1, GString& s2)
{
    Character* chars = s1.chars;
    s1.chars = s2.chars;
    s2.chars = chars;
    
    StringSize size = s1.size;
    s1.size = s2.size;
    s2.size = size;
    
    s1.check();
    s2.check();
}

bool operator<(GString const& a, GString const& b)
{
    int minSize = (a.getSize() < b.getSize()) ? a.getSize() : b.getSize();
    for (StringSize i = 0; i < minSize; i++)
    {
        if (a[i] < b[i])    return true;
        if (b[i] < a[i])    return false;
    }
    return a.getSize() < b.getSize();
}

void GString::check()
{
    try
    {
        assert(size >= 0, "String size must be non-negative")
        if (chars == nullptr)
            assert(size == 0, "If chars pointer is null, size must be 0")
        if (size == 0)
            assert(chars == nullptr, "If string size is zero, character array pointer must be null")
    }
    catch(...)
    {
        delete[] chars;
        throw;
    }
}
