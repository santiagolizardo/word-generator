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
    Generator(std::list<string> trainingData, int order, double smoothing);
    string generate(Random *random);
    char getLetter(const string &name, Random *random);
};
