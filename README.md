# Procedural name generator

Procedural name generator based on a Markov-chain process. Inspired by https://www.samcodes.co.uk/project/markov-namegen/

## Build instructions

```shell
conan install .
cmake --build --preset conan-release
build/Release/wordgenerator
```

## How it works

This program uses [Markov chains](https://en.wikipedia.org/wiki/Markov_chain) to procedurally generate original names. Given a set of words as training data, the name generator calculates the probability of a letter appearing after the sequence of letters chosen so far.

The generator maintains models that look up to "n" characters back, where "n" is the "Order". It starts by checking the highest order model, falling back to lower order models as necessary, using an approach called [Katz's back-off model](https://en.wikipedia.org/wiki/Katz%27s_back-off_model). As you increase the "Order" setting, larger chunks of the training words will appear in the generated output.

The Dirichlet "Prior" adds a constant probability that any letter may be picked as the next letter. It acts like an additive smoothing factor, making the generated name content a bit more "random". Keep this parameter small, it can be useful to increase this to get more results.

The generator generates as many names as possible, then filters and sorts the results according to the criteria "Length" which limits how many characters long the words are.

The "Similar To" parameter allows you to sort the generated names by their similarity to the name that you enter. The similarity of the words is determined by the <a href="https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance" target="_blank">Damerau-Levenshtein</a> distance.

This generator is suitable for generating all sorts of names.