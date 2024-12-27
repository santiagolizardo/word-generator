#pragma once

#include "Generator.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <optional>
using std::optional;

#include "Random.hpp"

class NameGenerator : public Generator
{
public:
    NameGenerator(const std::list<string> &trainingData, int order, double smoothing);
    optional<string> generateName(int minLength, int maxLength, int maxDistance, const optional<string> &similarTo, Random *random);
    std::unordered_set<string> generateNames(int count, int length, Random *random);
    std::unordered_set<string> generateNames(int count, int minLength, int maxLength, int maxDistance, const optional<string> &similarTo, Random *random);
};
