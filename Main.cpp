#include <args.hxx>

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include "NameGenerator.hpp"
#include "TrainingData.hpp"
#include "Random.hpp"

int main()
{
    const int order = 3;// "Highest order of model to use. Will use Katz's back-off model. It looks "
    //"for the next letter based on the last \"n\" letters."

    const double prior = 0.01; // "The prior adds a constant probability that a random letter is picked "
    //"from the alphabet when generating a new letter. Must be a number between 0 "
    //"and 1."

    TrainingData trainingData;
    trainingData.loadFromDisk();

    NameGenerator generator(trainingData.words, order, prior);

    constexpr int namesToGenerate = 10; // "Amount of names to generate."
    const std::list<string> names = generator.generateNames(namesToGenerate, 5, 25, 10, std::nullopt, new Random());

    for (const auto &name : names)
    {
        std::cout << name << std::endl;
    }

    return 0;
}
