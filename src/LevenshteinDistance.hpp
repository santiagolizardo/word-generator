#pragma once

#include <string>
using std::string;

class LevenshteinDistance
{
public:
    static int compute(const string &s, const string &t);
};