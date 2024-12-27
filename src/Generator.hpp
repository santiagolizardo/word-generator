#pragma once

#include <string>
using std::string;
#include <list>
#include <vector>
#include <unordered_set>

#include "Model.hpp"
#include "Random.hpp"

class Generator
{

public:
    int order;
    double smoothing;

private:
    std::list<Model> models;

public:
    Generator(const std::list<string>& trainingData, int order, double smoothing);
    string generate(Random *random);
    char predictNextCharacter(const string &name, Random *random);
};
