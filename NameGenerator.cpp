#include "NameGenerator.hpp"
#include "Generator.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include "LevenshteinDistance.hpp"
#include "Random.hpp"

NameGenerator::NameGenerator(const std::list<string> &trainingData, int order, double smoothing) : Generator(trainingData, order, smoothing)
{
}

optional<string> NameGenerator::generateName(int minLength, int maxLength, int maxDistance, optional<string> similarTo, Random *random)
{
    string name = generate(random);
    size_t pos;
    while ((pos = name.find('#')) != std::string::npos)
    {
        name.replace(pos, 1, ""); // Replace the character at position `pos` with an empty string
    }

    if (name.size() < minLength || name.size() > maxLength)
    {
        cout << "Rejected because of length: " << name << endl;
        return std::nullopt;
    }

    if (similarTo.has_value() && LevenshteinDistance::compute(similarTo.value(), name) > maxDistance)
    {
        cout << "Rejected because not similar: " << name << endl;
        return std::nullopt;
    }

    return name;
}

std::list<string> NameGenerator::generateNames(int count, int length, Random *random)
{
    return generateNames(count, length, length, 0, std::nullopt, random);
}

std::list<string> NameGenerator::generateNames(int count, int minLength, int maxLength, int maxDistance, optional<string> similarTo, Random *random)
{
    std::list<string> names;

    while (names.size() < count)
    {
        if (optional<string> name = generateName(minLength, maxLength, maxDistance, similarTo, random); name.has_value())
        {
            names.push_back(name.value());
        }
    }

    return names;
}