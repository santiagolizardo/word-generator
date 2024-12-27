#include "Model.hpp"

#include <list>
#include <map>
#include <stdexcept>
#include <vector>

#include <string>
using std::string;

#include <algorithm>

#include "Random.hpp"

Model::Model(std::list<string> trainingData, int order, double smoothing, std::vector<char> alphabet) : order{order},
                                                                                                        smoothing{smoothing},
                                                                                                        alphabet{alphabet}
{
    retrain(trainingData);
}

char Model::generate(string context, Random *random)
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
                std::list<char> &v = it->second;
                v.push_back(data[i + order]);
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
            int count = std::count(observations[context].begin(), observations[context].end(), prediction);
            chain.push_back(smoothing + count);
        }
    }
}

int Model::selectIndex(std::list<double> chain, Random *random)
{
    std::vector<double> totals;

    double accumulator = 0;
    for (const auto weight : chain)
    {
        accumulator += weight;
        totals.push_back(accumulator);
    }

    const double r = random->next() * accumulator;

    for (int i = 0; i < totals.size(); i++)
    {
        if (r < totals[i])
        {
            return i;
        }
    }

    return 0;
}
