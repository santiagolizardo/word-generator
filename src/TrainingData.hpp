#pragma once

#include <list>

#include <string>
using std::string;

class TrainingData {
public:
    void loadFromDisk(const std::string &path);

    std::list<string> words;
};
