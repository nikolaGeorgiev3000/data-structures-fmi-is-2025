#pragma once // VarTable.hpp

#include <cctype> // For std::toupper usage

constexpr int VAR_TABLE_SIZE = 26;
constexpr char VAR_FIRST_NAME = 'A';
constexpr char VAR_LAST_NAME = 'Z';

struct VarTable
{
public:
    bool hasValue[VAR_TABLE_SIZE];
    double value[VAR_TABLE_SIZE];

    VarTable();

    bool get(char name, double& outValue) const;
    void set(char name, double v);

private:
    static int indexFromName(char name)
    {
        unsigned char c = static_cast<unsigned char>(name);
        c = static_cast<unsigned char>(std::toupper(c));

        if (c < VAR_FIRST_NAME || c > VAR_LAST_NAME)
            return -1;

        return static_cast<int>(c - VAR_FIRST_NAME);
    }
};

// Implementations for 'VarTable' structure

inline VarTable::VarTable()
{
    for (size_t i = 0; i < VAR_TABLE_SIZE; ++i)
    {
        hasValue[i] = false;
        value[i] = 0.0;
    }
}

inline bool VarTable::get(char name, double& outValue) const
{
    int idx = indexFromName(name);

    if (idx < 0)
        return false;
    if (!hasValue[idx])
        return false;

    outValue = value[idx];
    return true;
}

inline void VarTable::set(char name, double v)
{
    int idx = indexFromName(name);

    if (idx < 0)
        return; // Invalid variable name, ignore

    hasValue[idx] = true;
    value[idx] = v;
}