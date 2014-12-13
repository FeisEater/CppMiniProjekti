#include "gstring.h"
//delete this
#include <iostream>

//helper function: return either a or b based on which is bigger
StringSize max(StringSize a, StringSize b)
{
    return (a > b) ? a : b;
}

/*
 * Helper function to set data members as they would be after default construction
 */
void GString::setDefaultValues()
{
    size = 0;
    space = minSize;
    chars = new Character[space];
}

/*
 * Helper function to restore values from backup
 */
void GString::restoreValues(const GString& backup)
{
    size = backup.size;
    space = backup.space;
    chars = backup.chars;
}

/*
 * Copy constructor
 * Precondition: GString to be copied from passes its invariant
 * Postcondition: Constructed GString passes its invariant
 * Strong exception guarantee
 */
GString::GString(GString const& string)
{
    try {string.check();}
    catch (...)
    {
        //Precondition fail, default constructor functionality
        setDefaultValues();
        throw;
    }
    
    size = string.size;
    space = max(size * 2, minSize);
    chars = new Character[space];
    for (StringSize i = 0; i < string.size; i++)
        chars[i] = string.chars[i];
    
    try {check();}
    catch(...)
    {
        //Postcondition fail, cleanup and default constructor functionality
        delete[] chars;
        setDefaultValues();
        throw;
    }
}

/*
 * Move constructor
 * Precondition: GString to be moved from passes its invariant
 * PostCondition: Constructed GString passes its invariant
 * Note: Previously given GString will not pass its invariant after this operation
 * Strong exception guarantee
 */
GString::GString(GString&& string)
{
    try {string.check();}
    catch (...)
    {
        //Precondition fail, default constructor functionality
        setDefaultValues();
        throw;
    }
    
    size = string.size;
    space = string.space;
    chars = string.chars;
    string.chars = nullptr;

    try {check();}
    catch(...)
    {
        //Postcondition fail, cleanup and default constructor functionality
        delete[] chars;
        setDefaultValues();
        throw;
    }
}

/*
 * Type conversion from c_string
 * No precondition, c_string assumed to be valid
 * PostCondition: Constructed GString passes its invariant
 * Strong exception guarantee
 */
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

    try {check();}
    catch(...)
    {
        //Postcondition fail, cleanup and default constructor functionality
        delete[] chars;
        setDefaultValues();
        throw;
    }
}

/*
 * Access indexed characters
 * Precondition: index within range
 * No postcondition, no changes to GString are made
 */
Character &GString::operator[](StringSize i) const
{
    if (i < 0 || i >= size)
        throw std::out_of_range("requested GString character index out of range");
    return chars[i];
}

/*
 * Copy assignment
 * Precondition: GString to be copied from passes its invariant
 * Postcondition: Constructed GString passes its invariant
 * Strong exception guarantee
 */
GString& GString::operator=(GString const& string)
{
    string.check(); //On fail throw exception and go no further
    
    const GString backup(*this);
    
    fitMoreCharacters(string.size - size);
    size = string.size;
    shrinkCharContainer();
    for (StringSize i = 0; i < string.size; i++)
        chars[i] = string[i];
    
    try {check();}
    catch (...)
    {
        //On postcondition fail restore original values
        restoreValues(backup);
        throw;
    }
    return *this;
}

/*
 * Move assignment
 * Precondition: GString to be moved from passes its invariant
 * No postcondition. All data values are moved trivially, therefore we have confidence
 *  that if precondition passed then newly constructed string will pass its invariant
 * Note: Previously given GString will not pass its invariant after this operation
 */
GString& GString::operator=(GString&& string)
{
    string.check();
    
    delete[] chars;
    size = string.size;
    space = string.space;
    chars = string.chars;
    string.chars = nullptr;
    return *this;
}

/*
 * True if GStrings are equal
 * Precondition: checked GStrings pass their invariant
 * No postcondition, no modifications
 */
bool operator==(GString const& a, GString const& b)
{
    a.check();
    b.check();
    
    if (a.getSize() != b.getSize())
        return false;
    for (StringSize i = 0; i < a.getSize(); ++i)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

/*
 * Constructs new GString which is s1 and s2 concatinated
 * Precondition: s1 and s2 pass their invariant
 * Postcondition: returned GString passes its invariant
 */
GString operator+(const GString& s1, const GString& s2)
{
    s1.check();
    s2.check();
    
    GString result = GString(s1);
    result += s2;
    
    result.check(); //if this fails, exception is thrown and no string is returned
    
    return result;
}

/*
 * Modifies this GString by concatinating s2 into it
 * Precondition: s2 passes its invariant
 * Postcindition: this GString passes its invariant
 * Strong exception guarantee
 */
GString& GString::operator+=(const GString& s2)
{
    s2.check();
    
    const GString backup(*this);
    fitMoreCharacters(s2.size);
    for (int i = 0; i < s2.size; ++i)
        chars[i + size] = s2[i];
    size += s2.size;
    
    try {check();}
    catch (...)
    {
        //On postcondition fail restore original values
        restoreValues(backup);
        throw;
    }
    
    return *this;
}

/*
 * Pushes character c to the end of the char array
 * No preconditions, character assumed to be valid.
 * Postcondition: Modified GString passes its invariant
 * Strong exception guarantee
 */
void GString::push_back(const Character c)
{
    const GString backup(*this);
    
    fitMoreCharacters(1);
    chars[size] = c;
    ++size;
    
    try {check();}
    catch (...)
    {
        //On postcondition fail restore original values
        restoreValues(backup);
        throw;
    }
}

/*
 * Removes last character from the string and returns it
 * Precondition: GString has characters in it. If it's not true,
 *      no modifications are made and 0 is returned
 * Postcondition: Modified GString passes its invariant
 * strong exception guarantee
 */
const Character GString::pop_back()
{
    if (size == 0)
        return 0;
    
    const GString backup(*this);
    
    Character c = chars[size - 1];
    --size;
    shrinkCharContainer();
    
    try {check();}
    catch(...)
    {
        restoreValues(backup);
        throw;
    }
    
    return c;
}

/*
 * Inserts string before pos:th character
 * Precondition: pos is within range, note that string can be inserted after last character
 *      Inserted string passes its invariant
 * Postcondition: Modified GString passes its invariant
 */
void GString::insert(StringSize pos, const GString& string)
{
    string.check();
    if (pos < 0 || pos > size)
        throw std::out_of_range("Can't insert out of range");
    
    const GString backup(*this);
    
    fitMoreCharacters(string.size);
    size += string.size;
    for (StringSize i = size - 1; i >= pos; --i)
    {
        chars[i + string.size] = chars[i];
        if (i == 0) break;
    }
    for (StringSize i = 0; i < string.size; ++i)
        chars[i + pos] = string[i];
    
    try {check();}
    catch(...)
    {
        restoreValues(backup);
        throw;
    }
}

/*
 * Inserts character after pos:th character in the GString
 * Precondition: pos is within range, note that character c can be inserted after last character
 * Postcondition: Modified GString passes its invariant
 */
void GString::insert(StringSize pos, const Character c)
{
    if (pos < 0 || pos > size)
        throw std::out_of_range("Can't insert out of range");
    
    const GString backup(*this);

    fitMoreCharacters(1);
    ++size;
    for (int i = size - 1; i >= pos; --i)
    {
        chars[i + 1] = chars[i];
        if (i == 0) break;
    }
    chars[pos] = c;

    try {check();}
    catch(...)
    {
        restoreValues(backup);
        throw;
    }
}

/*
 * Erases character from index start, end, and any characters inbetween
 * Precondition: start and end within range, start is less than or equal to end
 * Postcondition: modified GString passes the invariant
 * Strong exception guarantee
 */
void GString::erase(StringSize start, StringSize end)
{
    if (start < 0 || end >= size)
        throw std::out_of_range("Parameters out of range");
    if (start > end)
        throw std::domain_error("For 'erase' first argument must be less than second argument");
    
    const GString backup(*this);
    
    for (int i = end + 1; i < size; ++i)
        chars[i - end - 1 + start] = chars[i];
    size -= end - start + 1;
    shrinkCharContainer();

    try {check();}
    catch(...)
    {
        restoreValues(backup);
        throw;
    }
}

/*
 * Outputs GString into the stream
 * Precondition: obj passes the invariant
 * No postcondition, no modification to the GString
 */
std::ostream& operator<<(std::ostream& os, const GString& obj)
{
    obj.check();
    for (Character c : obj)
        os << c;
    return os;
}

//Helper function to determine whether c is whitespace (could have used standard library, whatever, I don't trust it)
bool isWhiteSpace(Character c)
{
    const Character whitespaces[6] = {' ', '\f', '\n', '\r', '\t', '\v'};
    for (Character w : whitespaces)
        if (c == w) return true;
    return false;
}

/*
 * Construct GString from the input stream. Whitespace ends GString construction
 * (constructed GString don't contain whitespace, whitespace separates GStrings)
 * No precondition, input stream assumed to be valid
 * Postcondition: constructed GString passes its invariant
 * Basic exception guarantee
 */
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

/*
 * Swaps content of two GString references
 * Precondition: GStrings to be swapped pass their invariant
 * No postcondition, it's assumed that swapped strings are valid if they're valid before swap
 */
void swap (GString& s1, GString& s2)
{
    s1.check();
    s2.check();

    Character* chars = s1.chars;
    s1.chars = s2.chars;
    s2.chars = chars;
    
    StringSize size = s1.size;
    s1.size = s2.size;
    s2.size = size;
    
    StringSize space = s1.space;
    s1.space = s2.space;
    s2.space = space;
}

/*
 * Check the alphabetical order of two GStrings.
 * Precondition: GStrings pass their invariant
 * No postcondition, no modification
 */
bool operator<(GString const& a, GString const& b)
{
    a.check();
    b.check();
    
    int minSize = (a.getSize() < b.getSize()) ? a.getSize() : b.getSize();
    for (StringSize i = 0; i < minSize; i++)
    {
        if (a[i] < b[i])    return true;
        if (b[i] < a[i])    return false;
    }
    return a.getSize() < b.getSize();
}

/*
 * Returns CString representation of this GString
 * No precondition
 * Postcondition: returned string has null termination at expected spot
 * Note: if GString contained null characters in the middle, they will remain in CString
 */ 
char* GString::to_C_string()
{
    char* result = new char[size + 1];
    char* currentPointer;
    currentPointer = result;
    for (Character c : *this)
    {
        *currentPointer = c;
        ++currentPointer;
    }
    *currentPointer = '\0';
    
    //Postcondition
    if (result[size] != '\0')
    {
        delete[] result;
        throw std::length_error("No null character at expected position");
    }
    return result;
}

bool GString::hasSubstring(const GString& sub)
{
    return false;
}

/*
 * Prepares introduction of given amount of characters by increasing the char array if necessary
 */
void GString::fitMoreCharacters(StringSize additionalChars)
{
    if (size + additionalChars >= space)
        replaceCharContainer(2 * (size + additionalChars));
}

/*
 * Shrinks char array if ratio of available space to real string length is too big
 */
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

/*
 * Replaces current char array with the new one, which is allocated by given amount of characters
 */
void GString::replaceCharContainer(StringSize newSize)
{
    Character* oldchars = chars;
    space = newSize;
    chars = new Character[space];
    for (int i = 0; i < size; ++i)
        chars[i] = oldchars[i];
    delete[] oldchars;
}

/*
 * Checks GString invariant, throws assertion_fail
 */
void GString::check() const
{
    assert(size >= 0, "String size must be non-negative")
    assert(space >= minSize, "Allocated char array length was too small")
    assert(size <= space, "String size is beyond character array size")
    assert(chars != nullptr, "Char array pointer can't be null")
}

Character& GString::Iterator::operator*()
{
    checkIndex();
    return string[index];
}

Character* GString::Iterator::operator->()
{
    checkIndex();
    return string.chars + index;
}

//pre-increment
GString::Iterator& GString::Iterator::operator++()
{
    ++index;
    return *this;
}

//post-increment
GString::Iterator GString::Iterator::operator++(int)
{
    Iterator it(*this);
    ++index;
    return it;
}

//checks whether stored index is within bounds
void GString::Iterator::checkIndex()
{
    if (index < 0 || index >= string.size)
        throw std::out_of_range("Iterator index out of bounds");
}