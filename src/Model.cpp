#include "Model.hpp"

#include <list>
#include <map>
#include <stdexcept>
#include <vector>

#include <string>
using std::string;

#include <algorithm>

#include "Random.hpp"

Model::Model(const std::list<string> &trainingData, int order, double smoothing, const std::vector<char> &alphabet) : order{order},
                                                                                                        smoothing{smoothing},
                                                                                                        alphabet{alphabet}
{
    retrain(trainingData);
}

char Model::generate(const string &context, Random *random)
{
    auto it = chains.find(context);
    if (it != chains.end())
    {
        const std::list<double> &chain = it->second;
        return alphabet[selectIndex(chain, random)];
    }
    return '\0';
}

void Model::retrain(const std::list<string> &trainingData)
{
    train(trainingData);
    buildChains();
}

void Model::train(const std::list<string> &trainingData)
{
    if (trainingData.empty()) {
        throw std::invalid_argument("trainingData is empty");
    }

    for (const auto& d : trainingData)
    {
        string data = string(order, '#') + d + '#';
        for (int i = 0; i < data.size() - order; i++)
        {
            string key = data.substr(i, order);
            if (auto it = observations.find(key); it == observations.end())
            {
                std::list<char> value;
                observations[key] = value;
            }
            else
            {
                it->second.push_back(data[i + order]);
            }
        }
    }
}

void Model::buildChains()
{
    for (const auto &[context, value] : observations)
    {
        for (char prediction : alphabet)
        {
            std::list<double>& chain = chains[context];
            int count = std::ranges::count(observations[context], prediction);
            chain.push_back(smoothing + count);
        }
    }
}

int Model::selectIndex(const std::list<double> &chain, Random *random)
{
    std::vector<double> totals;

    double accumulator = 0.0;

    for (const auto weight : chain)
    {
        accumulator += weight;
        totals.push_back(accumulator);
    }

    const double r = random->nextDouble() * accumulator;

    for (int i = 0; i < totals.size(); i++)
    {
        if (r < totals[i])
        {
            return i;
        }
    }

    return 0;
}
