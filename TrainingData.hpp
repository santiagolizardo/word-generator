#pragma once

#include <string>
using std::string;

#include <list>

class TrainingData
{

public:
    void loadFromDisk();
    std::list<string> words;
};
