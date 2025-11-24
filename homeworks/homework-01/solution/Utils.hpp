#pragma once // Utils.hpp

#include <cctype>  // std::toupper
#include <cstddef> // size_t
#include <cstring> // std::strlen, std::memcpy

// Whitespace check
inline bool isSpaceChar(char c)
{
    return c == ' ' || c == '\t' || c == '\r';
}

// Digit check
inline bool isDigitChar(char c)
{
    return c >= '0' && c <= '9';
}

// Letter check (ASCII only)
inline bool isLetterChar(char c)
{
    unsigned char uc = static_cast<unsigned char>(c);
    return (uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z');
}

// Copy error message to fixed buffer
inline void setError(char* buffer, size_t bufferSize, const char* msg)
{
    if (!buffer || bufferSize == 0)
        return;

    size_t len = std::strlen(msg);
    if (len >= bufferSize)
        len = bufferSize - 1;

    std::memcpy(buffer, msg, len);
    buffer[len] = '\0';
}

// Case insensitive compare of p[0..len-1] with UPPERCASE keyword
inline bool equalsIgnoreCase(const char* p, const char* keyword, size_t len)
{
    for (size_t i = 0; i < len && keyword[i] != '\0'; ++i)
    {
        char c = static_cast<char>(
            std::toupper(static_cast<unsigned char>(p[i])));
        if (c != keyword[i])
            return false;
    }

    return keyword[len] == '\0';
}