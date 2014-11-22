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