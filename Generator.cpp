#include "Generator.hpp"

#include <string>
using std::string;
#include <list>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "Model.hpp"
#include "Random.hpp"

Generator::Generator(std::list<string> trainingData, int order, double smoothing) : order{order}, smoothing{smoothing}
{
	std::unordered_set<char> letters;
	for (auto &word : trainingData)
	{
		for (char c : word)
		{
			letters.insert(c);
		}
	}
	std::vector<char> domain{letters.begin(), letters.end()};
	std::ranges::sort(domain);
	domain.insert(domain.begin(), '#');

	for (int i = 0; i < order; i++)
	{
		models.emplace_back(trainingData, order - i, smoothing, domain);
	}
}

string Generator::generate(Random *random)
{
	string name(order, '#');
	char letter = getLetter(name, random);
	while (letter != '#' && letter != '\0')
	{
		name += letter;
		letter = getLetter(name, random);
	}
	return name;
}

char Generator::getLetter(const string &name, Random *random)
{
	char letter = '\0';
	string context = name.substr(name.size() - order);
	for (auto &model : models)
	{
		letter = model.generate(context, random);
		if (letter == '\0')
		{
			context = context.substr(1);
		}
		else
		{
			break;
		}
	}
	return letter;
}
