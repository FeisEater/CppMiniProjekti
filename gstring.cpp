#include "gstring.h"
//delete this
#include <iostream>

StringSize max(StringSize a, StringSize b)
{
    return (a > b) ? a : b;
}

GString::GString(GString const& string) : size(string.size)
{
    space = max(size * 2, minSize);
    chars = new Character[space];
    for (StringSize i = 0; i < string.size; i++)
        chars[i] = string.chars[i];
    check();
}

GString::GString(GString&& string) : size(string.size), space(string.space), chars(string.chars)
{
    string.chars = nullptr;
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
    space = max(size * 2, minSize);
    chars = new Character[space];
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
    fitMoreCharacters(string.size - size);
    size = string.size;
    shrinkCharContainer();
    for (StringSize i = 0; i < string.size; i++)
        chars[i] = string[i];
    check();
    return *this;
}

GString& GString::operator=(GString&& string)
{
    delete[] chars;
    size = string.size;
    space = string.space;
    chars = string.chars;
    string.chars = nullptr;
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
    GString result = GString(s1);
    result += s2;
    return result;
}

GString& GString::operator+=(const GString& s2)
{
    fitMoreCharacters(s2.size);
    for (int i = 0; i < s2.size; ++i)
        chars[i + size] = s2[i];
    size += s2.size;
    check();
    return *this;
}

void GString::push_back(const Character c)
{
    fitMoreCharacters(1);
    chars[size] = c;
    ++size;
    check();
}

const Character GString::pop_back()
{
    if (size == 0)
        return 0;
    Character c = chars[size - 1];
    --size;
    shrinkCharContainer();
    check();
    return c;
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
        obj.push_back(c);
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

void GString::fitMoreCharacters(StringSize additionalChars)
{
    if (size + additionalChars >= space)
        replaceCharContainer(2 * (size + additionalChars));
}

void GString::shrinkCharContainer()
{
    if (size == 0)
    {
        if (space > minSize)
            replaceCharContainer(minSize);
    }
    else if (space > size * minSize)
        replaceCharContainer(2 * size);
}

void GString::replaceCharContainer(StringSize newSize)
{
    Character* oldchars = chars;
    space = newSize;
    chars = new Character[space];
    for (int i = 0; i < size; ++i)
        chars[i] = oldchars[i];
    delete[] oldchars;
}

void GString::check()
{
    try
    {
        assert(size >= 0, "String size must be non-negative")
        assert(space >= minSize, "Allocated char array length was too small")
        assert(size <= space, "String size is beyond character array size")
        assert(chars != nullptr, "Char array pointer can't be null")
    }
    catch(...)
    {
        delete[] chars;
        throw;
    }
}
