#pragma once

#include <list>
#include <map>
#include <vector>

#include <string>
using std::string;

#include "Random.hpp"

class Model
{
private:
    int order;
    double smoothing;
    std::vector<char> alphabet;
    std::map<string, std::list<char>> observations;
    std::map<string, std::list<double>> chains;

public:
    Model(std::list<string> trainingData, int order, double smoothing, std::vector<char> alphabet);

    char generate(string context, Random *random);

    void retrain(const std::list<string> &trainingData);

    void train(const std::list<string> &trainingData);

    void buildChains();

    int selectIndex(std::list<double> chain, Random *random);
};
