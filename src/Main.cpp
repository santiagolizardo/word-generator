#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <argparse/argparse.hpp>

#include "Version.hpp"
#include "NameGenerator.hpp"
#include "TrainingData.hpp"
#include "Random.hpp"

int main(int argc, char **argv) {
    argparse::ArgumentParser program(argv[0], PROJECT_VERSION);

    int minLength, maxLength;
    std::optional<std::string> similarTo;

    std::string trainingDataPath;
    int maxDistance;

    program.add_argument("--training-data-path")
            .required()
            .help("Path to where the JSON training data is")
            .store_into(trainingDataPath);
    program.add_argument("--model-order")
            .default_value(3)
            .help(
                "Highest order of model to use. Will use Katz's back-off model. It looks for the next letter based on the last \"n\" letters.")
            .scan<'d', int>();
    program.add_argument("--model-prior")
            .default_value(0.01)
            .help("The prior adds a constant probability that a random letter is picked from the alphabet when generating a new letter. Must be a number between 0 and 1")
            .scan<'g', double>();
    program.add_argument("--num-words")
            .default_value(10)
            .help("Number of words to generate")
            .scan<'d', int>();
    program.add_argument("--min-word-length")
            .default_value(3)
            .help("Minimum length of the word(s) to generate")
            .scan<'d', int>()
            .store_into(minLength);
    program.add_argument("--max-word-length")
            .default_value(15)
            .help("Maximum length of the word(s) to generate")
            .scan<'d', int>()
            .store_into(maxLength);
    program.add_argument("--similar-word")
            .default_value(std::nullopt)
            .help("Finds words similar to this one");
    program.add_argument("--similar-word-distance")
            .default_value(3)
            .help("Max distance (difference) to the similar word")
            .scan<'d', int>()
            .store_into(maxDistance);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return EXIT_FAILURE;
    }

    const int order = program.get<int>("model-order");

    const double prior = program.get<double>("model-prior");

    TrainingData trainingData;
    trainingData.loadFromDisk(trainingDataPath);

    NameGenerator generator(trainingData.words, order, prior);

    const int namesToGenerate = program.get<int>("num-words");
    const std::unordered_set<string> names = generator.generateNames(namesToGenerate, minLength, maxLength, maxDistance,
                                                            similarTo, new Random());

    for (const auto &name: names) {
        std::cout << name << std::endl;
    }

    return EXIT_SUCCESS;
}
