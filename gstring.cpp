#include "gstring.h"

GString::GString(const char* s) : chars(s)
{
    size = 0;
    while (*s)
    {
        ++s;
        ++size;
    }
}

const Character &GString::operator[](int i) const
{
    if (i < 0 || i > size)
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